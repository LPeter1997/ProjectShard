#include "AttractorUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			void AttractorUpdater::Update(float delta, ParticleArray* particles)
			{
				const uint end = particles->m_AliveCount;
				const uint attrCount = m_Attractors.size();
				
				Maths::Vector4f off;
				float dist;
				uint a;

				for (uint i = 0; i < end; i++)
				{
					for (a = 0; a < attrCount; a++)
					{
						off.x = m_Attractors[a].x - particles->Positions[i].x;
						off.y = m_Attractors[a].y - particles->Positions[i].y;
						off.z = m_Attractors[a].z - particles->Positions[i].z;
						dist = Maths::Vector4f::DotProduct(off, off);

						dist = m_Attractors[a].w / dist;

						particles->Accelerations[i] += Maths::Vector4f(dist * off.x, dist * off.y, dist * off.z, 0.0f);
					}
				}
			}
		}
	}
}