#pragma once

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include "../Windows/WinWindow.h"
#include "../../Types.h"

namespace Shard
{
	namespace Gfx
	{
		namespace DX
		{
			class D3D
			{
			private:
				static constexpr uint s_FrameBufferCount = 2;

				static ID3D12CommandAllocator* s_CommandAllocator[s_FrameBufferCount];
				static ID3D12GraphicsCommandList* s_CommandList;
				static ID3D12Resource* s_RenderTargets[s_FrameBufferCount];
				static ID3D12DescriptorHeap* s_RtvDescriptorHeap;
				static ID3D12Device* s_Device;
				static ID3D12CommandQueue* s_CommandQueue;
				static IDXGISwapChain3* s_SwapChain;
				static ID3D12Fence* s_Fence[s_FrameBufferCount];
				static HANDLE s_FenceEvent;
				static UINT64 s_FenceValue[s_FrameBufferCount];
				static uint s_FrameIndex;
				static uint s_RtvDescriptorSize;

			private:
				D3D() = delete;

			public:
				static bool Initialize();
				static void WaitForGPU();
				static void UpdatePipeline();
				static void Present();
				static void Terminate();
			};
		}
	}
}