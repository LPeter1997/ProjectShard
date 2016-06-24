#pragma once

#include "Button.h"

namespace Shard
{
	namespace Input
	{
		class MouseState
		{
		private:
			friend class Mouse;

		private:
			Button m_Buttons[(unsigned int)Buttons::__NumButtons];

		private:
			MouseState(Button* buttons);

		public:
			bool IsButtonDown(Buttons button) const;
			bool IsButtonUp(Buttons button) const;
		};
	}
}