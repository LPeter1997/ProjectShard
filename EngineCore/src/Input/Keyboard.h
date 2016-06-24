#pragma once

#include "Key.h"
#include "KeyboardState.h"

namespace Shard
{
	namespace Input
	{
		class Keyboard
		{
		private:
			static Key s_Keys[(unsigned int)Keys::__NumKeys];

		private:
			Keyboard() {}

		public:
			static inline void SetKeyCallback(GLFWwindow* window) { glfwSetKeyCallback(window, key_callback); }

			static void Update();

			static bool IsKeyPressed(Keys keycode);
			static bool IsKeyReleased(Keys keycode);
			static bool IsKeyDown(Keys keycode);

			static inline KeyboardState Keyboard::GetState()
			{
				return KeyboardState(s_Keys);
			}

		private:
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		};
	}
}