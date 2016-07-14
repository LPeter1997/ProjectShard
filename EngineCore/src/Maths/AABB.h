#pragma once

#include "Vector2.h"

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct AABB
		{
		public:
			Maths::Vector2f Position;
			Maths::Vector2f Size;

		public:
			AABB(const Maths::Vector2f& position, const Maths::Vector2f& size)
				: Position(position), Size(size)
			{
			}

			AABB(const Maths::Vector2f& size)
				: Position(Maths::Vector2f(0, 0)), Size(size)
			{
			}

			AABB()
				: Position(Maths::Vector2f(0, 0)), Size(Maths::Vector2f(0, 0))
			{
			}
		};

		typedef AABB<int> AABBi;
		typedef AABB<float> AABBf;
		typedef AABB<double> AABBd;
	}
}