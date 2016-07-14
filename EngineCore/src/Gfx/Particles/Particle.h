#pragma once

#include "../../Maths/Vector2.h"
#include "../../Maths/Vector4.h"
#include "../../Types.h"

namespace Shard
{
	namespace Gfx
	{
		struct Particle
		{
		public:
			Maths::Vector2f Position;
			Maths::Vector2f Velocity;
			float Life;
			uint Color;
			float Rotation;
			float Scale;

		public:
			Particle(const Maths::Vector2f& pos, const Maths::Vector2f& vel, float life, const Maths::Vector4f& color, float rot, float scl);
		};
	}
}