#pragma once

#include "../ParticleGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			class BasicTimeGenerator : public ParticleGenerator
			{
			public:
				float MinTime;
				float MaxTime;

			public:
				BasicTimeGenerator() {}

				void Generate(float delta, ParticleArray* particles, uint start, uint end) override;
			};
		}
	}
}