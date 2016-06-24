#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Patterns\Static.h"
#include "Debugging\Logger.h"
#include "Gfx\Shader\ShaderFactory.h"

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

			if (!glfwInit())
			{
				Debugging::Logger::Log<Debugging::Fatal>() << "Could not initialize GLFW!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "GLFW initialized successfully!" << std::endl;

			s_Initialized = true;
			return true;
		}

		static inline void Deinitialize()
		{
			if (!s_Initialized)
				return;

			Gfx::ShaderFactory::DisposeAll();
			glfwTerminate();
			Debugging::Logger::Log<Debugging::Info>() << "GLFW terminated!" << std::endl;
			s_Initialized = false;
		}
	};

	bool Core::s_Initialized = false;
}