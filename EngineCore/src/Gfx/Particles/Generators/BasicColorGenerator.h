#pragma once

#include "../ParticleGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			class BasicColorGenerator : public ParticleGenerator
			{
			public:
				Maths::Vector4f MinStartColor;
				Maths::Vector4f MaxStartColor;
				Maths::Vector4f MinEndColor;
				Maths::Vector4f MaxEndColor;

			public:
				BasicColorGenerator() {}

				void Generate(float delta, ParticleArray* particles, uint start, uint end) override;
			};
		}
	}
}