#pragma once

#include "../../Maths/Vector2.h"

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
			float Rotation;
			float Scale;

		public:
			Particle(const Maths::Vector2f& pos, const Maths::Vector2f& vel, float life, float rot, float scl);
		};
	}
}