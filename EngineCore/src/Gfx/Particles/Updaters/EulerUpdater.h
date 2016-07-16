#pragma once

#include "../ParticleUpdater.h"
#include "../../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleUpdaters
		{
			class EulerUpdater : public ParticleUpdater
			{
			public:
				Maths::Vector4f GlobalAcceleration;

			public:
				void Update(float delta, ParticleArray* particles) override;
			};
		}
	}
}