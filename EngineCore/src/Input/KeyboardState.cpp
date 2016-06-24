#include <cstring>
#include "KeyboardState.h"

namespace Shard
{
	namespace Input
	{
		KeyboardState::KeyboardState(Key* keys)
		{
			std::memcpy(m_Keys, keys, sizeof(Key) * (unsigned int)Keys::__NumKeys);
		}

		bool KeyboardState::IsKeyDown(Keys key) const
		{
			return m_Keys[(unsigned int)key].CurrentState;
		}

		bool KeyboardState::IsKeyUp(Keys key) const
		{
			return !m_Keys[(unsigned int)key].CurrentState;
		}
	}
}