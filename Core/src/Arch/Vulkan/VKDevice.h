#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include <Vulkan\vulkan.h>

namespace Shard
{
	namespace Gfx
	{
		namespace VK
		{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
			typedef HMODULE VkLibrary;
#elif defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
			typedef void* VkLibrary;
#endif

			class Device
			{
			private:
				static VkLibrary s_Library;

			private:
				Device() = delete;

			public:
				static bool Create();
			};
		}
	}
}