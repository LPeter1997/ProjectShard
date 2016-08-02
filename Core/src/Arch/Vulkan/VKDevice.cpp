#include <cstring>
#include <vector>
#include "VKDevice.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		namespace VK
		{
			static PFN_vkCreateInstance							vkCreateInstance = NULL;
			static PFN_vkEnumerateInstanceLayerProperties		vkEnumerateInstanceLayerProperties = NULL;
			static PFN_vkEnumerateInstanceExtensionProperties	vkEnumerateInstanceExtensionProperties = NULL;

			bool Device::Win32_LoadVulkan()
			{
				HMODULE vulkanLibrary = LoadLibrary("vulkan-1.dll");
				if (!vulkanLibrary)
				{
					Debugging::Logger::d() << "Failed to load Vulkan library!" << std::endl;
					return false;
				}

				if
				(
					(!Win32_LoadFunction(vulkanLibrary, vkCreateInstance, "vkCreateInstance")) ||
					(!Win32_LoadFunction(vulkanLibrary, vkEnumerateInstanceLayerProperties, "vkEnumerateInstanceLayerProperties")) ||
					(!Win32_LoadFunction(vulkanLibrary, vkEnumerateInstanceExtensionProperties, "vkEnumerateInstanceExtensionProperties"))
				)
					return false;

				return true;
			}

			bool Device::Create()
			{
				// Application info structure
				VkApplicationInfo appInfo = {};
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pApplicationName = "Shard Application";
				appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.pEngineName = "Shard Engine";
				appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.apiVersion = VK_API_VERSION_1_0;

				// Instance info structure
				VkInstanceCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				createInfo.pApplicationInfo = &appInfo;

				// Load validation layers
				const std::vector<const char*> validationLayers =
				{
					"VK_LAYER_LUNARG_standard_validation"
				};
				const bool enableValidationLayers = true;	// TODO: only in debug

				if (enableValidationLayers)
				{
					uint32 layerCount = 0;
					vkEnumerateInstanceLayerProperties(&layerCount, NULL);
					if (layerCount == 0)
					{
						Debugging::Logger::d() << "Could not load VK any validation layer" << std::endl;
						return false;
					}

					// Layers found, check if we have what we need
					std::vector<VkLayerProperties> availableLayers(layerCount);
					vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

					for (const char* layerName : validationLayers)
					{
						bool layerFound = false;
						for (const auto& layerProp : availableLayers)
						{
							if (std::strcmp(layerName, layerProp.layerName) == 0)
							{
								layerFound = true;
								break;
							}
						}

						if (!layerFound)
						{
							Debugging::Logger::d() << "Could not find VK validation layer: " << layerName << std::endl;
							return false;
						}
					}

					// Write layers in create info
					createInfo.enabledLayerCount = validationLayers.size();
					createInfo.ppEnabledLayerNames = validationLayers.data();
				}
				else
				{
					// No layers are enabled
					createInfo.enabledLayerCount = 0;
				}

				// Load extensions
				std::vector<const char*> extensionsNeeded =
				{
					VK_KHR_WIN32_SURFACE_EXTENSION_NAME, VK_KHR_SURFACE_EXTENSION_NAME
				};
				if (enableValidationLayers)
				{
					extensionsNeeded.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
				}

				uint32 extensionCount = 0;
				vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
				std::vector<VkExtensionProperties> availableExtensions(extensionCount);
				vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, availableExtensions.data());
				for (const char* extName : extensionsNeeded)
				{
					bool extFound = false;
					for (const auto& extProp : availableExtensions)
					{
						if (std::strcmp(extName, extProp.extensionName) == 0)
						{
							extFound = true;
							break;
						}

						if (!extFound)
						{
							Debugging::Logger::d() << "Could not find VK extension: " << extName << std::endl;
							return false;
						}
					}
				}

				// Create the instance
				VkInstance instance;
				if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
				{
					Debugging::Logger::d() << "Could not create VK device" << std::endl;
					return false;
				}

				return true;
			}
		}
	}
}