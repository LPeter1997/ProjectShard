#include "ParticleSystem.h"

namespace Shard
{
	namespace Gfx
	{
		ParticleSystem::ParticleSystem(uint max)
			: m_MaxCount(max), m_Particles(max)
		{
			for (uint i = 0; i < max; i++)
				m_Particles.Alives[i] = false;
		}

		void ParticleSystem::Update(float delta)
		{
			for (auto& em : m_Emitters)
			{
				em->Emit(delta, &m_Particles);
			}

			for (uint i = 0; i < m_MaxCount; i++)
			{
				m_Particles.Accelerations[i] = Maths::Vector4f(0, 0, 0, 0);
			}

			for (auto& ud : m_Updaters)
			{
				ud->Update(delta, &m_Particles);
			}
		}

		void ParticleSystem::Reset()
		{
			m_Particles.m_AliveCount = 0;
		}
	}
}