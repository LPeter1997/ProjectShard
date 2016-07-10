#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <OpenAL\al.h>
#include <OpenAL\alc.h>
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
		static ALCdevice* s_ALDevice;
		static ALCcontext* s_ALContext;

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

			s_ALDevice = alcOpenDevice(nullptr);
			if (!s_ALDevice)
			{
				Debugging::Logger::Log<Debugging::Fatal>() << "Could not initialize OpenAL!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "OpenAL initialized successfully!" << std::endl;

			s_ALContext = alcCreateContext(s_ALDevice, nullptr);

			if (!s_ALContext)
			{
				Debugging::Logger::Log<Debugging::Fatal>() << "Could not create OpenAL context!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "OpenAL context created successfully!" << std::endl;

			alcMakeContextCurrent(s_ALContext);

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

			alcMakeContextCurrent(nullptr);
			alcDestroyContext(s_ALContext);
			alcCloseDevice(s_ALDevice);
			Debugging::Logger::Log<Debugging::Info>() << "OpenAL terminated!" << std::endl;

			s_Initialized = false;
		}

		static inline void glfw_error_callback(int error, const char* msg)
		{
			Debugging::Logger::Log<Debugging::Error>() << "GLFW error[" << error << "] - '" << msg << "'!" << std::endl;
		}
	};

	bool Core::s_Initialized = false;
	ALCdevice* Core::s_ALDevice = nullptr;
	ALCcontext* Core::s_ALContext = nullptr;
}