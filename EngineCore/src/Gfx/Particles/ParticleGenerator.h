#pragma once

#include "ParticleArray.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleGenerator
		{
		public:
			virtual ~ParticleGenerator() {}

			virtual void Generate(float dt, ParticleArray* particles, uint start, uint end) = 0;
		};
	}
}