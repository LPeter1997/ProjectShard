#pragma once

#include "ParticleArray.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleUpdater
		{
		public:
			virtual ~ParticleUpdater() {}

			virtual void Update(float delta, ParticleArray* particles) = 0;
		};
	}
}