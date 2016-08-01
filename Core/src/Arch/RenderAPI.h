#pragma once

#define PLATFORM_OpenGL

namespace Shard
{
	namespace Platform
	{
		enum class RenderAPI
		{
			NoAPI, OpenGL, DirectX
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
	}
}