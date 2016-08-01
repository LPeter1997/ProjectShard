#pragma once

/*
DirectX rendering context
Supported OS: Windows
*/

#include "D3D.h"
#include "../Platform.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace DX
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
					Debugging::Logger::f() << "Could not initialize Direct3D context (Operating System not supported)!" << std::endl;
					return false;
				}

				template <>
				static inline bool Initialize<Platform::OperatingSystem::Windows>()
				{
					if (!D3D::Initialize())
					{
						Debugging::Logger::f() << "Failed to initialize Direct3D context!" << std::endl;
						return false;
					}

					Debugging::Logger::i() << "Direct3D context initialized successfully!" << std::endl;

					return true;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////

				// Destroy ///////////////////////////////////////////////////////////////////////////////////////////////
				template <Platform::OperatingSystem A = Platform::GetOS()>
				static inline void Destroy()
				{
					Debugging::Logger::f() << "Could not destroy Direct3D context (Operating System not supported)!" << std::endl;
				}

				template <>
				static inline void Destroy<Platform::OperatingSystem::Windows>()
				{
					D3D::Terminate();
					Debugging::Logger::i() << "Direct3D context destroyed!" << std::endl;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////

				// Present ///////////////////////////////////////////////////////////////////////////////////////////////
				template <Platform::OperatingSystem A = Platform::GetOS()>
				static inline void Present()
				{
					Debugging::Logger::f() << "Could not present Direct3D context (Operating System not supported)!" << std::endl;
				}

				template <>
				static inline void Present<Platform::OperatingSystem::Windows>()
				{
					D3D::Present();
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////
			};
		}
	}
}