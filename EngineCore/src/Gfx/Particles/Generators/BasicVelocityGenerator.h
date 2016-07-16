#pragma once

#include "../ParticleGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			class BasicVelocityGenerator : public ParticleGenerator
			{
			public:
				Maths::Vector4f MinVel;
				Maths::Vector4f MaxVel;

			public:
				BasicVelocityGenerator() {}

				void Generate(float delta, ParticleArray* particles, uint start, uint end) override;
			};
		}
	}
}