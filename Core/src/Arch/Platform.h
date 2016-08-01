#pragma once

#define PLATFORM_DirectX
#define OS_Windows

namespace Shard
{
	namespace Platform
	{
		enum class RenderAPI
		{
			NoAPI, OpenGL, DirectX
		};

		enum class OperatingSystem
		{
			NoOS, Windows
		};

		constexpr RenderAPI GetRenderAPI()
		{
#ifdef PLATFORM_OpenGL
			return RenderAPI::OpenGL;
#else
#ifdef PLATFORM_DirectX
			return RenderAPI::DirectX;
#else
			return RenderAPI::NoAPI;
#endif
#endif
		}

		constexpr OperatingSystem GetOS()
		{
#ifdef OS_Windows
			return OperatingSystem::Windows;
#else
			return OperatingSystem::NoOS;
#endif
		}
	}
}