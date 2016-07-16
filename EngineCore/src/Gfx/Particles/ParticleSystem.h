#pragma once

#include <vector>
#include "ParticleArray.h"
#include "ParticleEmitter.h"
#include "ParticleUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleSystem
		{
		private:
			uint m_MaxCount;
			ParticleArray m_Particles;
			std::vector<ParticleEmitter*> m_Emitters;
			std::vector<ParticleUpdater*> m_Updaters;

		public:
			ParticleSystem(uint max);

			void Update(float delta);
			void Reset();

			inline void AddEmitter(ParticleEmitter* em) { m_Emitters.push_back(em); }
			inline void AddUpdater(ParticleUpdater* ud) { m_Updaters.push_back(ud); }

			inline uint ParticleCount() const { return m_MaxCount; }
			inline uint AliveParticleCount() const { return m_Particles.m_AliveCount; }
			inline const ParticleArray* ParticleData() const { return &m_Particles; }
		};
	}
}