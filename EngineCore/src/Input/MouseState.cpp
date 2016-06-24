#include <cstring>
#include "MouseState.h"

namespace Shard
{
	namespace Input
	{
		MouseState::MouseState(Button* buttons)
		{
			std::memcpy(m_Buttons, buttons, sizeof(Button) * (unsigned int)Buttons::__NumButtons);
		}

		bool MouseState::IsButtonDown(Buttons button) const
		{
			return m_Buttons[(unsigned int)button].CurrentState;
		}

		bool MouseState::IsButtonUp(Buttons button) const
		{
			return !m_Buttons[(unsigned int)button].CurrentState;
		}
	}
}