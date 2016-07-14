#pragma once

#include "Renderers\Renderer2D.h"

namespace Shard
{
	namespace Gfx
	{
		class Animation
		{
		public:
			virtual void Update(float delta) = 0;
			virtual void Draw(const Maths::Vector3f& position, Renderer2D& renderer) = 0;
		};
	}
}