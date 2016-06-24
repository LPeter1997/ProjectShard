#include <iostream>
#include <GLFW\glfw3.h>
#include "src\Debugging\Logger.h"

using namespace Shard;
using namespace Debugging;

int main(void)
{
	if (!glfwInit())
		std::cout << "noinit" << std::endl;
	else
		std::cout << "YEE" << std::endl;

	system("PAUSE");
	return 0;
}