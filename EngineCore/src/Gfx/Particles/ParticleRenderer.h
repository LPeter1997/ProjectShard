#pragma once

#include "ParticleSystem.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleRenderer
		{
		public:
			virtual ~ParticleRenderer() {}

			virtual void Generate(ParticleSystem* system) = 0;
			virtual void Destroy() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
		};
	}
}