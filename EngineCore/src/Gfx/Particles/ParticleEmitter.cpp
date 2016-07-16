#include <algorithm>
#include "ParticleEmitter.h"

namespace Shard
{
	namespace Gfx
	{
		ParticleEmitter::ParticleEmitter(float emitRate)
			: m_EmitRate(emitRate)
		{
		}

		void ParticleEmitter::Emit(float delta, ParticleArray* particles)
		{
			float gen = delta * m_EmitRate + m_LeftOver;
			const uint maxNewParts = (uint)(gen);
			m_LeftOver = gen - (float)maxNewParts;

			const uint start = particles->m_AliveCount;
			const uint end = std::min(start + maxNewParts, particles->m_Count - 1);

			// Generators
			for (ParticleGenerator* gen : m_Generators)
			{
				gen->Generate(delta, particles, start, end);
			}

			// Waking
			for (uint i = start; i < end; i++)
			{
				particles->Revive(i);
			}
		}
	}
}