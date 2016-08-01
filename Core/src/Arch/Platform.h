#pragma once

#define PLATFORM_DirectX
#define OS_Windows

namespace Shard
{
	namespace Platform
	{
		enum class RenderAPI
		{
			NoAPI, OpenGL, DirectX, Vulkan
		};

		enum class OperatingSystem
		{
			NoOS, Windows
		};

		constexpr RenderAPI GetRenderAPI()
		{
#if defined(PLATFORM_OpenGL)
			return RenderAPI::OpenGL;
#elif defined(PLATFORM_DirectX)
			return RenderAPI::DirectX;
#else
			return RenderAPI::NoAPI;
#endif
		}

		constexpr OperatingSystem GetOS()
		{
#if defined(OS_Windows)
			return OperatingSystem::Windows;
#else
			return OperatingSystem::NoOS;
#endif
		}
	}
}