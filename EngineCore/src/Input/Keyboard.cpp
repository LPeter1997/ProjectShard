#include "Keyboard.h"

namespace Shard
{
	namespace Input
	{
		Key Keyboard::s_Keys[(unsigned int)Keys::__NumKeys];

		void Keyboard::Update()
		{
			for (unsigned int i = 0; i < (unsigned int)Keys::__NumKeys; i++)
			{
				s_Keys[i].Released = (s_Keys[i].LastState && !s_Keys[i].CurrentState);
				s_Keys[i].Pressed = (!s_Keys[i].LastState && s_Keys[i].CurrentState);

				s_Keys[i].LastState = s_Keys[i].CurrentState;
			}
		}

		bool Keyboard::IsKeyPressed(Keys keycode)
		{
			if ((unsigned int)keycode >= (unsigned int)Keys::__NumKeys)
			{
				// TODO
				// Logging
				return false;
			}

			return s_Keys[(unsigned int)keycode].Pressed == 1;
		}

		bool Keyboard::IsKeyReleased(Keys keycode)
		{
			if ((unsigned int)keycode >= (unsigned int)Keys::__NumKeys)
			{
				// TODO
				// Logging
				return false;
			}

			return s_Keys[(unsigned int)keycode].Released == 1;
		}

		bool Keyboard::IsKeyDown(Keys keycode)
		{
			if ((unsigned int)keycode >= (unsigned int)Keys::__NumKeys)
			{
				// TODO
				// Debug logging
				return false;
			}

			return s_Keys[(unsigned int)keycode].CurrentState == 1;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_RELEASE)
			{
				Keyboard::s_Keys[key].CurrentState = false;
			}
			else
			{
				Keyboard::s_Keys[key].CurrentState = true;
			}
		}
	}
}