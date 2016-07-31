#pragma once

#include <type_traits>
#include "ContextAttribs.h"
#include "../Arch/RenderAPI.h"
#include "../Arch/OpenGL/GLContext.h"
#include "../Arch/DirectX/DXContext.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		class Context
		{
		private:
			Context() = delete;

		public:
			// Create ///////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline void Create(ContextAttribs const& attribs)
			{
				Debugging::Logger::f() << "Could not create rendering context (Rendering API not supported)!" << std::endl;
			}

			template <>
			static inline void Create<Platform::RenderAPI::OpenGL>(ContextAttribs const& attribs)
			{
				GL::Context::Create(attribs);
			}

			template <>
			static inline void Create<Platform::RenderAPI::DirectX>(ContextAttribs const& attribs)
			{
				DX::Context::Create(attribs);
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Update ///////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline void Update()
			{
				Debugging::Logger::f() << "Could not update rendering context (Rendering API not supported)!" << std::endl;
			}

			template <>
			static inline void Update<Platform::RenderAPI::OpenGL>()
			{
				GL::Context::Update();
			}

			template <>
			static inline void Update<Platform::RenderAPI::DirectX>()
			{
				DX::Context::Update();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// CloseRequested ///////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline bool CloseRequested()
			{
				Debugging::Logger::f() << "Rendering API not supported!" << std::endl;
				return false;
			}

			template <>
			static inline bool CloseRequested<Platform::RenderAPI::OpenGL>()
			{
				return GL::Context::CloseRequested();
			}

			template <>
			static inline bool CloseRequested<Platform::RenderAPI::DirectX>()
			{
				return DX::Context::CloseRequested();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Destroy //////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::RenderAPI A = Platform::GetRenderAPI()>
			static inline void Destroy()
			{
				Debugging::Logger::f() << "Rendering API not supported!" << std::endl;
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
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		};
	}
}