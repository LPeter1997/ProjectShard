#pragma once

#include "../ParticleUpdater.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			class BasicColorUpdater : public ParticleUpdater
			{
			public:
				void Update(float delta, ParticleArray* particles) override;
			};
		}
	}
}