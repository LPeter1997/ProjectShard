#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Window.h"
#include "../Debugging/Logger.h"
#include "../Input/Input.h"

namespace Shard
{
	namespace Gfx
	{
		Window::Window(const cstr title, uint width, uint height)
			: m_Title(title), m_Width(width), m_Height(height), m_Window(nullptr)
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
			if (!m_Window)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Failed to create window!" << std::endl;
				return;
			}

			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_size_callback);

			glfwMakeContextCurrent(m_Window);

			if (glewInit() != GLEW_OK)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Failed to initialize GLEW context!" << std::endl;
				return;
			}

			Debugging::Logger::Log<Debugging::Info>() << "GLEW context initialized successfully!" << std::endl;
			
			glfwSwapInterval(0);

			Input::Keyboard::SetKeyCallback(m_Window);
			Input::Mouse::SetButtonCallback(m_Window);
			Input::Mouse::SetCursorPositionCallback(m_Window);
		}

		Window::~Window()
		{
			Dispose();
		}

		void Window::Update() const
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				Debugging::Logger::Log<Debugging::Error>() << "OpenGL error: " << error << "!" << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void Window::SetSize(uint width, uint height)
		{
			glViewport(0, 0, width, height);
			glfwSetWindowSize(m_Window, width, height);
			m_Width = width;
			m_Height = height;
		}

		void Window::SetTitle(const cstr title)
		{
			glfwSetWindowTitle(m_Window, title);

			m_Title = title;
		}

		// Callbacks
		void Window::window_size_callback(GLFWwindow* window, int width, int height)
		{
			((Window*)glfwGetWindowUserPointer(window))->SetSize(width, height);
		}
	}
}