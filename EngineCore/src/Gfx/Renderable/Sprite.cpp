#include "Sprite.h"

namespace Shard
{
	namespace Gfx
	{
		Sprite::Sprite(const Maths::Vector2f& pos, const Maths::Vector2f& size)
			: Renderable2D(pos, size, 0xffffffff)
		{
		}
	}
}