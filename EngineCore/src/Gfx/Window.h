#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../Types.h"

namespace Shard
{
	namespace Gfx
	{
		class Window
		{
		private:
			cstr m_Title;
			uint m_Width, m_Height;
			GLFWwindow* m_Window;

		public:
			Window(const cstr title, uint width, uint height);
			~Window();

			void Update() const;
			void SetSize(uint width, uint height);
			void SetTitle(const cstr title);

			inline void MakeCurrent() const
			{
				glfwMakeContextCurrent(m_Window);
			}

			inline bool Window::IsCloseRequested() const
			{
				return glfwWindowShouldClose(m_Window) > 0;
			}

			inline bool Window::IsCreated() const
			{
				return m_Window != nullptr;
			}

			inline void Clear() const
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			inline void Dispose() const
			{
				if (IsCreated())
					glfwDestroyWindow(m_Window);
			}

			static inline Window* GetCurrent()
			{
				return (Window*)(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			}

		private:
			// Callbacks
			static void window_size_callback(GLFWwindow* window, int width, int height);
		};
	}
}