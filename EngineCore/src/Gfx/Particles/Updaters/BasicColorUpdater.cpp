#include "BasicColorUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			void BasicColorUpdater::Update(float delta, ParticleArray* particles)
			{
				const uint end = particles->m_AliveCount;
				for (uint i = 0; i < end; i++)
				{
					Maths::Vector4f diff = particles->EndColors[i] - particles->StartColors[i];
					Maths::Vector4f addc(particles->Times[i].z * diff.x, particles->Times[i].z * diff.y, particles->Times[i].z * diff.z, particles->Times[i].z * diff.w);
					particles->Colors[i] = particles->StartColors[i] + addc;
				}
			}
		}
	}
}