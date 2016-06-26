#pragma once

#include "Renderable2D.h"

namespace Shard
{
	namespace Gfx
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(const Maths::Vector2f& pos, const Maths::Vector2f& size);
		};
	}
}