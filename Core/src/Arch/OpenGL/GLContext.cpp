#include <GL/glew.h>
#include "GLContext.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace GL
		{
			GLFWwindow* Context::s_Window = nullptr;

			void Context::Create(ContextAttribs const& attribs)
			{
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
				s_Window = glfwCreateWindow(attribs.Width, attribs.Height, attribs.Title.c_str(), nullptr, nullptr);
				if (!s_Window)
				{
					Debugging::Logger::e() << "Failed to create GLFW window!" << std::endl;
					return;
				}

				Debugging::Logger::i() << "GLFW window created successfully!" << std::endl;

				glfwMakeContextCurrent(s_Window);

				if (glewInit() != GLEW_OK)
				{
					Debugging::Logger::Log<Debugging::Error>() << "Failed to initialize GLEW context!" << std::endl;
					return;
				}

				Debugging::Logger::Log<Debugging::Info>() << "GLEW context initialized successfully!" << std::endl;

				glfwSwapInterval(0);
			}

			void Context::Update()
			{
				glfwPollEvents();
				glfwSwapBuffers(s_Window);
				glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			bool Context::CloseRequested()
			{
				return glfwWindowShouldClose(s_Window) > 0;
			}

			void Context::Destroy()
			{
				glfwDestroyWindow(s_Window);
				Debugging::Logger::i() << "GLFW window destroyed!" << std::endl;
			}
		}
	}
}