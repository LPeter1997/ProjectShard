#pragma once

#include "Key.h"

namespace Shard
{
	namespace Input
	{
		class KeyboardState
		{
		private:
			friend class Keyboard;

		private:
			Key m_Keys[(unsigned int)Keys::__NumKeys];

		private:
			KeyboardState(Key* keys);

		public:
			KeyboardState() {}

		public:
			bool IsKeyDown(Keys key) const;
			bool IsKeyUp(Keys key) const;
		};
	}
}