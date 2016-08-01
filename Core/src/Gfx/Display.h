#pragma once

/*
Rendering context
Supported OS: Windows
*/

#include "DisplayAttribs.h"
#include "../Arch/Platform.h"
#include "../Arch/Windows/WinWindow.h"

namespace Shard
{
	namespace Gfx
	{
		class Display
		{
		private:
			Display() = delete;

		public:
			// Create ///////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::OperatingSystem A = Platform::GetOS()>
			static inline void Create(DisplayAttribs const& attribs)
			{
				Debugging::Logger::f() << "Could not create display (Operating System not supported)!" << std::endl;
			}

			// For Windows create a window
			template <>
			static inline void Create<Platform::OperatingSystem::Windows>(DisplayAttribs const& attribs)
			{
				Windows::Window::Create(attribs);
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Update ///////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::OperatingSystem A = Platform::GetOS()>
			static inline void Update()
			{
				Debugging::Logger::f() << "Could not update window (Operating System not supported)!" << std::endl;
			}

			template <>
			static inline void Update<Platform::OperatingSystem::Windows>()
			{
				Windows::Window::Update();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// CloseRequested ///////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::OperatingSystem A = Platform::GetOS()>
			static inline bool CloseRequested()
			{
				Debugging::Logger::f() << "Operating System not supported!" << std::endl;
				return false;
			}

			template <>
			static inline bool CloseRequested<Platform::OperatingSystem::Windows>()
			{
				return Windows::Window::CloseRequested();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Destroy //////////////////////////////////////////////////////////////////////////////////////////////////////
			template <Platform::OperatingSystem A = Platform::GetOS()>
			static inline void Destroy()
			{
				Debugging::Logger::f() << "Operating System not supported!" << std::endl;
			}

			template <>
			static inline void Destroy<Platform::OperatingSystem::Windows>()
			{
				Windows::Window::Destroy();
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		};
	}
}