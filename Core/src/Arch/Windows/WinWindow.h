#pragma once

#include <windows.h>
#include <windowsx.h>
#include "../../Gfx/DisplayAttribs.h"

namespace Shard
{
	namespace Gfx
	{
		namespace Windows
		{
			class Window
			{
			private:
				static bool s_Closed;
				static HWND s_Handle;
				static HDC s_ContextHandle;

			private:
				Window() = delete;

			public:
				static void Create(DisplayAttribs const& attribs);
				static void Update();
				static bool CloseRequested();
				static void Destroy();

				static inline HWND const& GetHandle() { return s_Handle; }
				static inline HDC const& GetContextHandle() { return s_ContextHandle; }

			private:
				static LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			};
		}
	}
}