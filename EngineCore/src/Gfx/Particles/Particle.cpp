#include "Particle.h"

namespace Shard
{
	namespace Gfx
	{
		Particle::Particle(const Maths::Vector2f& pos, const Maths::Vector2f& vel, float life, float rot, float scl)
			: Position(pos), Velocity(vel), Life(life), Rotation(rot), Scale(scl)
		{
		}
	}
}