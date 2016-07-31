#include <iostream>
#include <GLFW\glfw3.h>
#include "src\Shard.h"
#include "src\Debugging\Logger.h"
#include "src\Gfx\Context.h"

using namespace Shard;
using namespace Gfx;
using namespace Debugging;

int main(void)
{
	Core::Initialize();
	Context::Create(ContextAttribs({ 960, 540, "Shard Engine!" }));

	while (!Context::CloseRequested())
	{
		Context::Update();
	}

	Context::Destroy();
	Core::Terminate();

	system("PAUSE");
	return 0;
}