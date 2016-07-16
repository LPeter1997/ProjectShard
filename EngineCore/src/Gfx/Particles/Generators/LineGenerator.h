#pragma once

#include "../ParticleGenerator.h"
#include "../../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			class LineGenerator : public ParticleGenerator
			{
			public:
				Maths::Vector4f Start;
				Maths::Vector4f End;

			public:
				LineGenerator() {}

				void Generate(float delta, ParticleArray* particles, uint start, uint end) override;
			};
		}
	}
}