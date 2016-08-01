#include "WinWindow.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace Windows
		{
			bool Window::s_Closed = false;
			HWND Window::s_Handle;
			HDC Window::s_ContextHandle;

			void Window::Create(DisplayAttribs const& attribs)
			{
				// DX window attribs
				WNDCLASSEX wc;
				ZeroMemory(&wc, sizeof(WNDCLASSEX));

				// Fill attribs
				wc.cbSize = sizeof(WNDCLASSEX);
				wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
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
					Debugging::Logger::e() << "Failed to register Win32 class!" << std::endl;
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
					Debugging::Logger::e() << "Failed to create Win32 window!" << std::endl;
					return;
				}

				s_ContextHandle = GetDC(s_Handle);

				// Set the pixel format
				PIXELFORMATDESCRIPTOR pfd =
				{
					sizeof(PIXELFORMATDESCRIPTOR),
					1,
					PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
					PFD_TYPE_RGBA,
					16,
					0, 0, 0, 0, 0, 0,
					0,
					0,
					0,
					0, 0, 0, 0,
					16,
					0,
					0,
					PFD_MAIN_PLANE,
					0,
					0, 0, 0
				};

				int pixelFormat = ChoosePixelFormat(s_ContextHandle, &pfd);
				if (!pixelFormat)
				{
					Debugging::Logger::e() << "Failed to choose Win32 window pixel format!" << std::endl;
					return;
				}

				if (SetPixelFormat(s_ContextHandle, pixelFormat, &pfd) != TRUE)
				{
					Debugging::Logger::e() << "Failed to set Win32 window pixel format!" << std::endl;
					return;
				}

				Debugging::Logger::i() << "Win32 window created successfully!" << std::endl;

				// Display the window
				ShowWindow(s_Handle, SW_SHOW);
				UpdateWindow(s_Handle);
			}

			void Window::Update()
			{
				MSG msg;

				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			bool Window::CloseRequested()
			{
				return s_Closed;
			}

			void Window::Destroy()
			{
				ReleaseDC(s_Handle, s_ContextHandle);
				DestroyWindow(s_Handle);
				Debugging::Logger::i() << "Win32 window destroyed!" << std::endl;
			}

			LRESULT CALLBACK Window::window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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