#include "DXContext.h"
#include "../../Debugging/Logger.h"
#include "D3D.h"

namespace Shard
{
	namespace Gfx
	{
		namespace DX
		{
			bool Context::s_Closed = false;
			HWND Context::s_Handle;

			void Context::Create(ContextAttribs const& attribs)
			{
				// DX window attribs
				WNDCLASSEX wc;
				ZeroMemory(&wc, sizeof(WNDCLASSEX));

				// Fill attribs
				wc.cbSize = sizeof(WNDCLASSEX);
				wc.style = CS_HREDRAW | CS_VREDRAW;
				wc.lpfnWndProc = window_proc;
				wc.cbClsExtra = NULL;
				wc.cbWndExtra = NULL;
				wc.hInstance = GetModuleHandle(0);
				wc.hCursor = LoadCursor(NULL, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
				wc.lpszMenuName = NULL;
				wc.lpszClassName = "WindowClass1";

				// Register window
				if (!RegisterClassEx(&wc))
				{
					Debugging::Logger::e() << "Failed to register DirectX class!" << std::endl;
					return;
				}

				// Create client size
				RECT wr = { 0, 0, attribs.Width, attribs.Height };
				AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX), FALSE);

				// Window handle
				s_Handle = CreateWindowEx
				(
					NULL,
					"WindowClass1",
					attribs.Title.c_str(),
					WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX),
					CW_USEDEFAULT, CW_USEDEFAULT,
					wr.right - wr.left,
					wr.bottom - wr.top,
					NULL,
					NULL,
					GetModuleHandle(0),
					NULL
				);

				if (!s_Handle)
				{
					Debugging::Logger::e() << "Failed to create DirectX window!" << std::endl;
					return;
				}

				Debugging::Logger::i() << "DirectX window created successfully!" << std::endl;

				// Initialize Direct3D
				if (!D3D::Initialize())
				{
					Debugging::Logger::e() << "Failed to initialize Direct3D!" << std::endl;
					return;
				}

				Debugging::Logger::i() << "Direct3D initialized successfully!" << std::endl;

				// Display the window
				ShowWindow(s_Handle, SW_SHOW);
				UpdateWindow(s_Handle);
			}

			void Context::Update()
			{
				MSG msg;

				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					D3D::Present();
				}
			}

			bool Context::CloseRequested()
			{
				return s_Closed;
			}

			void Context::Destroy()
			{
				D3D::Terminate();
				Debugging::Logger::i() << "Direct3D terminated!" << std::endl;
				DestroyWindow(s_Handle);
				Debugging::Logger::i() << "DirectX window destroyed!" << std::endl;
			}

			LRESULT CALLBACK Context::window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
			{
				switch (message)
				{
				case WM_CLOSE:
					s_Closed = true;
					return 0;
					break;
				}

				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
	}
}