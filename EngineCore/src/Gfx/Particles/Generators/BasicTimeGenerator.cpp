#include "BasicTimeGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			void BasicTimeGenerator::Generate(float delta, ParticleArray* particles, uint start, uint end)
			{
				float diff = MaxTime - MinTime;

				for (uint i = start; i < end; i++)
				{
					float at = (float)std::rand() / (float)RAND_MAX;
					float t = MinTime + at;

					particles->Times[i].x = t;
					particles->Times[i].y = t;
					particles->Times[i].z = 0.0f;
					particles->Times[i].w = 1.0f / t;
				}
			}
		}
	}
}