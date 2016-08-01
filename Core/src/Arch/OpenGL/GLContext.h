#pragma once

/*
OpenGL rendering context
Supported OS: Windows
*/

#include <GL\glew.h>
#include <windows.h>
#include "../Platform.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace GL
		{
			class Context
			{
			private:
				Context() = delete;

			public:
				// Initialize ////////////////////////////////////////////////////////////////////////////////////////////
				template <Platform::OperatingSystem A = Platform::GetOS()>
				static inline bool Initialize()
				{
					Debugging::Logger::f() << "Could not initialize OpenGL context (Operating System not supported)!" << std::endl;
					return false;
				}

				template <>
				static inline bool Initialize<Platform::OperatingSystem::Windows>()
				{
					// First set the windows display as the current OpenGL context
					HDC hDC = Windows::Window::GetContextHandle();
					HGLRC hRC = wglCreateContext(hDC);

					if (!wglMakeCurrent(hDC, hRC))
					{
						Debugging::Logger::f() << "Failed to set Win32 OpenGL context!" << std::endl;
						return false;
					}

					// Initialize GLEW
					if (glewInit() != GLEW_OK)
					{
						Debugging::Logger::f() << "Failed to initialize OpenGL context!" << std::endl;
						return false;
					}

					Debugging::Logger::i() << "OpenGL context initialized successfully!" << std::endl;

					return true;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////

				// Destroy ///////////////////////////////////////////////////////////////////////////////////////////////
				template <Platform::OperatingSystem A = Platform::GetOS()>
				static inline void Destroy()
				{
					Debugging::Logger::f() << "Could not destroy OpenGL context (Operating System not supported)!" << std::endl;
				}

				template <>
				static inline void Destroy<Platform::OperatingSystem::Windows>()
				{
					wglMakeCurrent(Windows::Window::GetContextHandle(), NULL);
					wglDeleteContext(wglGetCurrentContext());
					Debugging::Logger::i() << "OpenGL context destroyed!" << std::endl;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////

				// Present ///////////////////////////////////////////////////////////////////////////////////////////////
				template <Platform::OperatingSystem A = Platform::GetOS()>
				static inline void Present()
				{
					Debugging::Logger::f() << "Could not present OpenGL context (Operating System not supported)!" << std::endl;
				}

				template <>
				static inline void Present<Platform::OperatingSystem::Windows>()
				{
					glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					SwapBuffers(Windows::Window::GetContextHandle());
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////
			};
		}
	}
}