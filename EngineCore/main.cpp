#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"

using namespace Shard;

int main(void)
{
	Core::Initialize();

	Gfx::Window display("Shard Engine", 960, 540);
	while (!display.IsCloseRequested())
	{
		display.Update();
	}

	display.Dispose();
	Core::Deinitialize();

	system("PAUSE");
	return 0;
}