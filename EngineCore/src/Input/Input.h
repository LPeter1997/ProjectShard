#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "../Patterns/Static.h"

namespace Shard
{
	namespace Input
	{
		class InputDevices : public Patterns::Static
		{
		public:
			static inline void Update()
			{
				Keyboard::Update();
				Mouse::Update();
			}
		};
	}
}