#pragma once

#include <GLFW\glfw3.h>
#include "../../Gfx/DisplayAttribs.h"

namespace Shard
{
	namespace Gfx
	{
		namespace GL
		{
			class Window
			{
			private:
				static GLFWwindow* s_Window;

			private:
				Window() = delete;

			public:
				static void Create(DisplayAttribs const& attribs);
				static void Update();
				static bool CloseRequested();
				static void Destroy();
			};
		}
	}
}