#pragma once

#include <windows.h>
#include <windowsx.h>
#include "../../Gfx/ContextAttribs.h"

namespace Shard
{
	namespace Gfx
	{
		namespace DX
		{
			class Context
			{
			private:
				static bool s_Closed;
				static HWND s_Handle;

			private:
				Context() = delete;

			public:
				static void Create(ContextAttribs const& attribs);
				static void Update();
				static bool CloseRequested();
				static void Destroy();

				static inline HWND const& GetHandle() { return s_Handle; }

			private:
				static LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			};
		}
	}
}