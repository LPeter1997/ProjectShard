#pragma once

#include <vector>
#include "../ParticleUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			class AttractorUpdater : public ParticleUpdater
			{
			private:
				std::vector<Maths::Vector4f> m_Attractors;	// W is force

			public:
				void Update(float delta, ParticleArray* particles) override;

				inline void AddAttractor(const Maths::Vector4f& position) { m_Attractors.push_back(position); }
				inline Maths::Vector4f& GetAttractor(uint idx) { return m_Attractors[idx]; }
			};
		}
	}
}