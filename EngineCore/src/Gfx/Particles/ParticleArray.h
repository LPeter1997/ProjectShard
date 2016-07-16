#pragma once

#include "../../Types.h"
#include "../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		struct ParticleArray
		{
		public:
			// Per particle
			Maths::Vector4f* Positions;
			Maths::Vector4f* Colors;
			Maths::Vector4f* StartColors;
			Maths::Vector4f* EndColors;
			Maths::Vector4f* Velocities;
			Maths::Vector4f* Accelerations;
			Maths::Vector4f* Times;
			bool* Alives;
			// Per particle cluster/array
			uint m_Count;
			uint m_AliveCount;

		public:
			ParticleArray(uint max);
			~ParticleArray();

			void Generate(uint max);

			void Kill(uint idx);
			void Revive(uint idx);
			void Swap(uint a, uint b);
		};
	}
}