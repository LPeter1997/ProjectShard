#include "D3D.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace DX
		{
			constexpr uint D3D::s_FrameBufferCount;

			ID3D12CommandAllocator* D3D::s_CommandAllocator[s_FrameBufferCount];
			ID3D12GraphicsCommandList* D3D::s_CommandList;
			ID3D12Resource* D3D::s_RenderTargets[s_FrameBufferCount];
			ID3D12DescriptorHeap* D3D::s_RtvDescriptorHeap;
			ID3D12Device* D3D::s_Device;
			ID3D12CommandQueue* D3D::s_CommandQueue;
			IDXGISwapChain3* D3D::s_SwapChain;
			ID3D12Fence* D3D::s_Fence[s_FrameBufferCount];
			HANDLE D3D::s_FenceEvent;
			UINT64 D3D::s_FenceValue[s_FrameBufferCount];
			uint D3D::s_FrameIndex;
			uint D3D::s_RtvDescriptorSize;

			bool D3D::Initialize()
			{
				bool fullscreen = false;

				HRESULT hr;

				IDXGIFactory4* dxgiFactory;
				hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
				if (FAILED(hr))
				{
					return false;
				}

				IDXGIAdapter1* adapter;
				int adapterIndex = 0;
				bool adapterFound = false;

				// Find the first DX12 compatible adapter (GPU)
				while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
				{
					// Get GPU info
					DXGI_ADAPTER_DESC1 desc;
					adapter->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
					{
						// Software device is refused
						adapterIndex++;
						continue;
					}

					// Need feature level 11 or higher
					hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr);
					//hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr);
					if (SUCCEEDED(hr))
					{
						adapterFound = true;
						break;
					}

					adapterIndex++;
				}

				if (!adapterFound)
				{
					return false;
				}

				// Found a DX12 compatible adapter, create it
				hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&s_Device));
				if (FAILED(hr))
				{
					return false;
				}

				// Create a command queue
				D3D12_COMMAND_QUEUE_DESC cqDesc = {};

				cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
				cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

				hr = s_Device->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&s_CommandQueue));
				if (FAILED(hr))
				{
					return false;
				}

				// Create the swap chain for multi-buffering
				DXGI_MODE_DESC backBufferDesc = {};
				backBufferDesc.Width = 0;			// Sets width automatically if 0
				backBufferDesc.Height = 0;			// Sets height automatically if 0
				backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

				// Don't need multisampling, 1 sampler needed
				DXGI_SAMPLE_DESC sampleDesc = {};
				sampleDesc.Count = 1;

				// Create the chain
				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferCount = s_FrameBufferCount;
				swapChainDesc.BufferDesc = backBufferDesc;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				swapChainDesc.OutputWindow = Windows::Window::GetHandle();
				swapChainDesc.SampleDesc = sampleDesc;
				swapChainDesc.Windowed = !fullscreen;		// TODO: add fullscreen
				
				IDXGISwapChain* tmpSwapChain;
				dxgiFactory->CreateSwapChain(s_CommandQueue, &swapChainDesc, &tmpSwapChain);

				s_SwapChain = static_cast<IDXGISwapChain3*>(tmpSwapChain);
				s_FrameIndex = s_SwapChain->GetCurrentBackBufferIndex();

				// Create back-buffer descriptor heap
				D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
				rtvHeapDesc.NumDescriptors = s_FrameBufferCount;
				rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

				// Not directly referenced by shaders
				rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// FLAG_SHADER_VISIBLE otherwise
				hr = s_Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&s_RtvDescriptorHeap));
				if (FAILED(hr))
				{
					return false;
				}

				// Get the size of a descriptor in the heap
				s_RtvDescriptorSize = s_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

				// Get handle to the first descriptor in the heap
				CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(s_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

				// Create a RTV for each buffer
				for (uint i = 0; i < s_FrameBufferCount; i++)
				{
					// Get the ith buffer
					hr = s_SwapChain->GetBuffer(i, IID_PPV_ARGS(&s_RenderTargets[i]));
					if (FAILED(hr))
					{
						return false;
					}

					// Create a render target
					s_Device->CreateRenderTargetView(s_RenderTargets[i], nullptr, rtvHandle);

					// Increment rtv handle by the descriptor's size
					rtvHandle.Offset(1, s_RtvDescriptorSize);
				}

				// Create command allocators
				for (uint i = 0; i < s_FrameBufferCount; i++)
				{
					hr = s_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&s_CommandAllocator[i]));
					if (FAILED(hr))
					{
						return false;
					}
				}

				// Create command list with first allocator
				hr = s_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, s_CommandAllocator[0], NULL, IID_PPV_ARGS(&s_CommandList));
				if (FAILED(hr))
				{
					return false;
				}
				// It's in recording state so closing is needed
				s_CommandList->Close();

				// Create a fence and fence event
				// Fence
				for (uint i = 0; i < s_FrameBufferCount; i++)
				{
					hr = s_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&s_Fence[i]));
					if (FAILED(hr))
					{
						return false;
					}
					s_FenceValue[i] = 0;	// Initial value
				}

				// Create handle for fence event
				s_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
				if (s_FenceEvent == nullptr)
				{
					return false;
				}

				return true;
			}

			void D3D::UpdatePipeline()
			{
				HRESULT hr;

				// Wait for the GPU to finish
				WaitForGPU();

				hr = s_CommandAllocator[s_FrameIndex]->Reset();
				if (FAILED(hr))
				{
					Debugging::Logger::e() << "Failed to reset DirectX command allocator!" << std::endl;
					return;
				}

				hr = s_CommandList->Reset(s_CommandAllocator[s_FrameIndex], NULL);
				if (FAILED(hr))
				{
					Debugging::Logger::e() << "Failed to reset DirectX command list!" << std::endl;
					return;
				}

				// Start recording commands
				// Render target from present state to the render target state
				s_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(s_RenderTargets[s_FrameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

				// Get the handle to current render target
				CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(s_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), s_FrameIndex, s_RtvDescriptorSize);

				// Set render target to the output of the pipeline
				s_CommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

				// Clear the render target
				const float clearColor[] = { 0.2f, 0.3f, 1.0f, 1.0f };
				s_CommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

				// Render target from render target state to present state
				s_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(s_RenderTargets[s_FrameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

				hr = s_CommandList->Close();
				if (FAILED(hr))
				{
					Debugging::Logger::e() << "Failed to close DirectX command list!" << std::endl;
					return;
				}
			}

			void D3D::Present()
			{
				HRESULT hr;

				UpdatePipeline();

				// Create an array of command lists
				ID3D12CommandList* ppCommandList[] = { s_CommandList };

				// Execute the array
				s_CommandQueue->ExecuteCommandLists(_countof(ppCommandList), ppCommandList);

				// At the end of the queue
				hr = s_CommandQueue->Signal(s_Fence[s_FrameIndex], s_FenceValue[s_FrameIndex]);
				if (FAILED(hr))
				{
					Debugging::Logger::e() << "Could not sign fence value at the end of command queue!" << std::endl;
					return;
				}

				// Present the current backbuffer
				hr = s_SwapChain->Present(0, 0);
				if (FAILED(hr))
				{
					Debugging::Logger::e() << "Failed to present the current backbuffer!" << std::endl;
					return;
				}
			}

			void D3D::Terminate()
			{
				// Wait for GPU to finish all frames before deallocating
				//for (uint i = 0; i < s_FrameBufferCount; i++)
				//{
					//s_FrameIndex = i;
				WaitForGPU();
				//}

				// Get swap chain out of fullscreen if it is
				BOOL fulls = false;
				if (s_SwapChain->GetFullscreenState(&fulls, NULL))
				{
					s_SwapChain->SetFullscreenState(false, NULL);
				}

				s_Device->Release();
				s_SwapChain->Release();
				s_CommandQueue->Release();
				s_RtvDescriptorHeap->Release();
				s_CommandList->Release();

				for (uint i = 0; i < s_FrameBufferCount; i++)
				{
					s_RenderTargets[i]->Release();
					s_CommandAllocator[i]->Release();
					s_Fence[i]->Release();
				}
			}

			void D3D::WaitForGPU()
			{
				HRESULT hr;

				// Swap the current rtv buffer index to draw on the correct buffer
				s_FrameIndex = s_SwapChain->GetCurrentBackBufferIndex();

				// If current fence value is less than fence value then the GPU hasn't finished
				if (s_Fence[s_FrameIndex]->GetCompletedValue() < s_FenceValue[s_FrameIndex])
				{
					// Create a signal to finish
					hr = s_Fence[s_FrameIndex]->SetEventOnCompletion(s_FenceValue[s_FrameIndex], s_FenceEvent);
					if (FAILED(hr))
					{
						Debugging::Logger::e() << "Could not signal GPU completition!" << std::endl;
						return;
					}

					// Wait until the event is triggered
					WaitForSingleObject(s_FenceEvent, INFINITE);
					//WaitForSingleObject(s_FenceEvent, 100);
				}

				// Increment fence value for next frame
				s_FenceValue[s_FrameIndex]++;
			}
		}
	}
}