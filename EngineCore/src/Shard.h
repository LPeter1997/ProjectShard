#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include "Patterns\Static.h"
#include "Debugging\Logger.h"
#include "Gfx\Shader\ShaderFactory.h"
#include "FreeTypeManager.h"

namespace Shard
{
	class Core : public Patterns::Static
	{
	private:
		static bool s_Initialized;

	public:
		static inline bool Initialize()
		{
			if (s_Initialized)
				return true;

			glfwSetErrorCallback(glfw_error_callback);

			if (!glfwInit())
			{
				Debugging::Logger::Log<Debugging::Fatal>() << "Could not initialize GLFW!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "GLFW initialized successfully!" << std::endl;
			
			FreeImage_Initialise();
			Debugging::Logger::Log<Debugging::Info>() << "FreeImage initialized successfully!" << std::endl;

			if (!FreeTypeManager::Initialize())
			{
				Debugging::Logger::Log<Debugging::Fatal>() << "Could not initialize FreeType!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "FreeType initialized successfully!" << std::endl;

			s_Initialized = true;
			return true;
		}

		static inline void Deinitialize()
		{
			if (!s_Initialized)
				return;

			Gfx::ShaderFactory::DisposeAll();
			Debugging::Logger::Log<Debugging::Info>() << "Disposed all shader programs!" << std::endl;

			glfwTerminate();
			Debugging::Logger::Log<Debugging::Info>() << "GLFW terminated!" << std::endl;
			
			FreeImage_DeInitialise();
			Debugging::Logger::Log<Debugging::Info>() << "FreeImage terminated!" << std::endl;

			FreeTypeManager::Deinitialize();
			Debugging::Logger::Log<Debugging::Info>() << "FreeType terminated!" << std::endl;

			s_Initialized = false;
		}

		static inline void glfw_error_callback(int error, const char* msg)
		{
			Debugging::Logger::Log<Debugging::Error>() << "GLFW error[" << error << "] - '" << msg << "'!" << std::endl;
		}
	};

	bool Core::s_Initialized = false;
}