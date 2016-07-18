#include "EulerUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			void EulerUpdater::Update(float delta, ParticleArray* particles)
			{
				//const Maths::Vector4f acc = Maths::Vector4f(delta * GlobalAcceleration.x, delta * GlobalAcceleration.y, delta * GlobalAcceleration.z, 0.0f);
				const uint end = particles->m_AliveCount;

				// Set acceleration
				for (uint i = 0; i < end; i++)
				{
					particles->Accelerations[i] += GlobalAcceleration;
				}

				// Accelerate
				for (uint i = 0; i < end; i++)
				{
					//Maths::Vector4f& pacc = particles->Accelerations[i];
					particles->Velocities[i] += Maths::Vector4f(delta * particles->Accelerations[i].x, delta * particles->Accelerations[i].y, delta * particles->Accelerations[i].z, 0.0f);
					//particles->Velocities[i] += particles->Accelerations[i];
				}

				// Reposition
				for (uint i = 0; i < end; i++)
				{
					particles->Positions[i] += Maths::Vector4f
						(
						delta * particles->Velocities[i].x, delta * particles->Velocities[i].y, delta * particles->Velocities[i].z, 0.0f
						);
				}
			}
		}
	}
}