#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"

using namespace Shard;

int main(void)
{
	Core::Initialize();

	Resources::ContentManager content("res");
	//Resources::Text* file = content.Load<Resources::Text>("test.txt");
	//std::cout << file->GetText() << std::endl;

	Gfx::Window display("Shard Engine", 960, 540);

	while (!display.IsCloseRequested())
	{
		display.Update();
		Input::Update();
	}

	display.Dispose();

	content.UnloadAll();
	Core::Deinitialize();
	return 0;
}