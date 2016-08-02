#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include <Vulkan\vulkan.h>
#include "../../Types.h"

namespace Shard
{
	namespace Gfx
	{
		namespace VK
		{
			class Device
			{
			private:
				Device() = delete;

			public:
				static bool Win32_LoadVulkan();
				static bool Create();

			private:
				template <typename T>
				static inline bool Win32_LoadFunction(const HMODULE& dev, T& fn, const char* name)
				{
					fn = (T)GetProcAddress(dev, name);
					if (!fn)
					{
						Debugging::Logger::e() << "Failed to load Vulkan function: '" << name << "'!" << std::endl;
						return false;
					}
					return true;
				}
			};
		}
	}
}