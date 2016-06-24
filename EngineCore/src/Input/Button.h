#pragma once

#include <GLFW\glfw3.h>

namespace Shard
{
	namespace Input
	{
		struct Button
		{
			unsigned char CurrentState : 1;
			unsigned char LastState : 1;

			unsigned char Pressed : 1;
			unsigned char Released : 1;
		};

		enum class Buttons
		{
			Left = GLFW_MOUSE_BUTTON_LEFT,
			Right = GLFW_MOUSE_BUTTON_RIGHT,
			Middle = GLFW_MOUSE_BUTTON_MIDDLE,
			B1 = GLFW_MOUSE_BUTTON_1,
			B2 = GLFW_MOUSE_BUTTON_2,
			B3 = GLFW_MOUSE_BUTTON_3,
			B4 = GLFW_MOUSE_BUTTON_4,
			B5 = GLFW_MOUSE_BUTTON_5,
			B6 = GLFW_MOUSE_BUTTON_6,
			B7 = GLFW_MOUSE_BUTTON_7,
			B8 = GLFW_MOUSE_BUTTON_8,
			__NumButtons = GLFW_MOUSE_BUTTON_LAST + 1
		};
	}
}