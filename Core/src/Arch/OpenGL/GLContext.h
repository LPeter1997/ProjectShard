#pragma once

#include <GLFW\glfw3.h>
#include "../../Gfx/ContextAttribs.h"

namespace Shard
{
	namespace Gfx
	{
		namespace GL
		{
			class Context
			{
			private:
				static GLFWwindow* s_Window;

			private:
				Context() = delete;

			public:
				static void Create(ContextAttribs const& attribs);
				static void Update();
				static bool CloseRequested();
				static void Destroy();
			};
		}
	}
}