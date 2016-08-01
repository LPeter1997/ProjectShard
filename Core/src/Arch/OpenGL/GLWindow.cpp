#include <GL/glew.h>
#include "GLWindow.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace GL
		{
			GLFWwindow* Window::s_Window = nullptr;

			void Window::Create(DisplayAttribs const& attribs)
			{
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
				s_Window = glfwCreateWindow(attribs.Width, attribs.Height, attribs.Title.c_str(), nullptr, nullptr);
				if (!s_Window)
				{
					Debugging::Logger::e() << "Failed to create GLFW window!" << std::endl;
					return;
				}

				Debugging::Logger::i() << "GLFW window created successfully!" << std::endl;

				/*
				glfwMakeContextCurrent(s_Window);
				glfwSwapInterval(0);
				*/
			}

			void Window::Update()
			{
				glfwPollEvents();
				glfwSwapBuffers(s_Window);
			}

			bool Window::CloseRequested()
			{
				return glfwWindowShouldClose(s_Window) > 0;
			}

			void Window::Destroy()
			{
				glfwDestroyWindow(s_Window);
				Debugging::Logger::i() << "GLFW window destroyed!" << std::endl;
			}
		}
	}
}