#include "BasicVelocityGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			void BasicVelocityGenerator::Generate(float delta, ParticleArray* particles, uint start, uint end)
			{
				Maths::Vector4f diff = MaxVel - MinVel;

				for (uint i = start; i < end; i++)
				{
					float at = (float)std::rand() / (float)RAND_MAX;
					Maths::Vector4f vel(at * diff.x + MinVel.x, at * diff.y + MinVel.y, at * diff.z + MinVel.z, 0);
					particles->Velocities[i] = vel;
				}
			}
		}
	}
}