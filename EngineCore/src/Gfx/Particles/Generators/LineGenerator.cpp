#include <cstdlib>
#include "LineGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			void LineGenerator::Generate(float delta, ParticleArray* particles, uint start, uint end)
			{
				Maths::Vector4f diff = End - Start;

				for (uint i = start; i < end; i++)
				{
					float at = (float)std::rand() / (float)RAND_MAX;
					Maths::Vector4f pos(at * diff.x + Start.x, at * diff.y + Start.y, at * diff.z + Start.z, 1.0f);
					particles->Positions[i] = pos;
				}
			}
		}
	}
}