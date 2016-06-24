#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace Shard
{
	namespace Input
	{
		inline void Update()
		{
			Keyboard::Update();
			Mouse::Update();
		}
	}
}