#include "Mouse.h"

namespace Shard
{
	namespace Input
	{
		Button Mouse::s_Buttons[(unsigned int)Buttons::__NumButtons];
		double Mouse::s_PosX;
		double Mouse::s_PosY;

		void Mouse::Update()
		{
			for (unsigned int i = 0; i < (unsigned int)Buttons::__NumButtons; i++)
			{
				s_Buttons[i].Released = (s_Buttons[i].LastState && !s_Buttons[i].CurrentState);
				s_Buttons[i].Pressed = (!s_Buttons[i].LastState && s_Buttons[i].CurrentState);

				s_Buttons[i].LastState = s_Buttons[i].CurrentState;
			}
		}

		bool Mouse::IsButtonPressed(Buttons button)
		{
			if ((unsigned int)button >= (unsigned int)Buttons::__NumButtons)
			{
				// TODO
				// Add logging
				return false;
			}

			return s_Buttons[(unsigned int)button].Pressed == 1;
		}

		bool Mouse::IsButtonReleased(Buttons button)
		{
			if ((unsigned int)button >= (unsigned int)Buttons::__NumButtons)
			{
				// TODO
				// Add logging
				return false;
			}

			return s_Buttons[(unsigned int)button].Released == 1;
		}

		bool Mouse::IsButtonDown(Buttons button)
		{
			if ((unsigned int)button >= (unsigned int)Buttons::__NumButtons)
			{
				// TODO
				// Add logging
				return false;
			}

			return s_Buttons[(unsigned int)button].CurrentState == 1;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_RELEASE)
			{
				Mouse::s_Buttons[button].CurrentState = false;
			}
			else
			{
				Mouse::s_Buttons[button].CurrentState = true;
			}
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Mouse::s_PosX = xpos;
			Mouse::s_PosY = ypos;
		}
	}
}