#pragma once

#include <GLFW\glfw3.h>
#include "Debugging\Logger.h"
#include "Arch\RenderAPI.h"

namespace Shard
{
	class Core
	{
	private:
		static bool s_Initialized;

	public:
		// Initialize
		template <Platform::RenderAPI A = Platform::GetRenderAPI()>
		static inline bool Initialize()
		{
			Debugging::Logger::f() << "Rendering API not supported!" << std::endl;
			return false;
		}

		template <>
		static inline bool Initialize<Platform::RenderAPI::OpenGL>()
		{
			if (s_Initialized)
				return true;

			if (!glfwInit())
			{
				Debugging::Logger::f() << "Could not initialize GLFW!" << std::endl;
				return false;
			}

			Debugging::Logger::i() << "GLFW initialized successfully!" << std::endl;

			s_Initialized = true;
			return true;
		}

		template <>
		static inline bool Initialize<Platform::RenderAPI::DirectX>()
		{
			if (s_Initialized)
				return true;

			Debugging::Logger::i() << "DirectX initialized successfully!" << std::endl;

			s_Initialized = true;
			return true;
		}

		// Terminate
		template <Platform::RenderAPI A = Platform::GetRenderAPI()>
		static inline void Terminate()
		{
			Debugging::Logger::f() << "Rendering API not supported!" << std::endl;
		}

		template <>
		static inline void Terminate<Platform::RenderAPI::OpenGL>()
		{
			if (!s_Initialized)
				return;

			glfwTerminate();
			Debugging::Logger::i() << "GLFW terminated!" << std::endl;

			s_Initialized = false;
		}

		template <>
		static inline void Terminate<Platform::RenderAPI::DirectX>()
		{
			if (!s_Initialized)
				return;

			Debugging::Logger::i() << "DirectX terminated!" << std::endl;

			s_Initialized = false;
		}
	};
}