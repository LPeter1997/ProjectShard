#include "BasicTimeUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			void BasicTimeUpdater::Update(float delta, ParticleArray* particles)
			{
				uint end = particles->m_AliveCount;

				for (uint i = 0; i < end; i++)
				{
					particles->Times[i].x -= delta;
					particles->Times[i].z = 1.0f - (particles->Times[i].x * particles->Times[i].w);

					if (particles->Times[i].x < 0.0f)
					{
						particles->Kill(i);
						end = particles->m_AliveCount < particles->m_Count ? particles->m_AliveCount : particles->m_Count;
					}
				}
			}
		}
	}
}