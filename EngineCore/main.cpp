#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"

using namespace Shard;

int main(void)
{
	Core::Initialize();

	Gfx::Window display("Shard Engine", 960, 540);
	while (!display.IsCloseRequested())
	{
		display.Update();
		Input::Update();

		if (Input::Keyboard::IsKeyDown(Input::Keys::A))
			std::cout << "a";
	}

	display.Dispose();
	Core::Deinitialize();
	return 0;
}