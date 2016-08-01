#pragma once

/*
Rendering context
Supported APIs: OpenGL, DirectX
*/

#include "../Arch/Platform.h"
#include "../Arch/OpenGL/GLContext.h"
#include "../Arch/DirectX/DXContext.h"

namespace Shard
{
	namespace Gfx
	{
		class Context
		{
		private:
			Context() = delete;

		public:
			// Initialize //////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline bool Initialize()
			{
				Debugging::Logger::f() << "Could not create rendering contect (Rendering API not supported)!" << std::endl;
				return false;
			}

			template <>
			static inline bool Initialize<Platform::RenderAPI::OpenGL>()
			{
				return GL::Context::Initialize();
			}

			template <>
			static inline bool Initialize<Platform::RenderAPI::DirectX>()
			{
				return DX::Context::Initialize();
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Present /////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline void Present()
			{
				Debugging::Logger::f() << "Could not present rendering contect (Rendering API not supported)!" << std::endl;
			}

			template <>
			static inline void Present<Platform::RenderAPI::OpenGL>()
			{
				GL::Context::Present();
			}

			template <>
			static inline void Present<Platform::RenderAPI::DirectX>()
			{
				DX::Context::Present();
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Destroy /////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline void Destroy()
			{
				Debugging::Logger::f() << "Could not destroy rendering contect (Rendering API not supported)!" << std::endl;
			}

			template <>
			static inline void Destroy<Platform::RenderAPI::OpenGL>()
			{
				GL::Context::Destroy();
			}

			template <>
			static inline void Destroy<Platform::RenderAPI::DirectX>()
			{
				DX::Context::Destroy();
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		};
	}
}