#pragma once

#include <vector>
#include "ParticleGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleEmitter
		{
		private:
			float m_EmitRate;
			std::vector<ParticleGenerator*> m_Generators;
			float m_LeftOver;

		public:
			ParticleEmitter(float emitRate);

			inline void AddParticleGenerator(ParticleGenerator* gen)
			{
				m_Generators.push_back(gen);
			}

			void Emit(float delta, ParticleArray* particles);
		};
	}
}