#include "VKDevice.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace VK
		{
			VkLibrary Device::s_Library;

			bool Device::Create()
			{
				PFN_vkCreateInstance vkCreateInstance = NULL;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
				s_Library = LoadLibrary("vulkan-1.dll");
#elif defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
				VulkanLibrary = dlopen("libvulkan.so.1", RTLD_NOW);
#endif
				if (!s_Library)
				{
					Debugging::Logger::d() << "Didnt load vulkan!" << std::endl;
					return false;
				}

				Debugging::Logger::d() << "YEEE" << std::endl;
				return true;
			}
		}
	}
}