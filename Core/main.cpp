#include <GL\glew.h>
#include <iostream>
#include <GLFW\glfw3.h>
#include "src\Debugging\Logger.h"
#include "src\Gfx\Display.h"
#include "src\Gfx\Context.h"
#include "src\Arch\Vulkan\VKDevice.h"

using namespace Shard;
using namespace Gfx;
using namespace Debugging;

int main(void)
{
	Display::Create(DisplayAttribs({ 960, 540, "Shard Engine!" }));
	VK::Device::Win32_LoadVulkan();
	VK::Device::Create();
	//Context::Initialize();

	while (!Display::CloseRequested())
	{
		//Context::Present();
		Display::Update();
	}

	//Context::Destroy();
	Display::Destroy();

	system("PAUSE");
	return 0;
}