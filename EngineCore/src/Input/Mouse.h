#pragma once

#include "Button.h"
#include "MouseState.h"

namespace Shard
{
	namespace Input
	{
		class Mouse
		{
		private:
			static Button s_Buttons[(unsigned int)Buttons::__NumButtons];
			static double s_PosX;
			static double s_PosY;

		private:
			Mouse() {}

		public:
			static inline void SetButtonCallback(GLFWwindow* window) { glfwSetMouseButtonCallback(window, mouse_button_callback); }
			static inline void SetCursorPositionCallback(GLFWwindow* window) { glfwSetCursorPosCallback(window, cursor_position_callback); }

			static void Update();

			static bool IsButtonPressed(Buttons button);
			static bool IsButtonReleased(Buttons button);
			static bool IsButtonDown(Buttons button);

			static inline double GetX() { return s_PosX; }
			static inline double GetY() { return s_PosY; }

			static inline MouseState Mouse::GetState()
			{
				return MouseState(s_Buttons);
			}

		private:
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}