#pragma once

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct AABB
		{
			T X, Y;
			T Width, Height;

			AABB(T x, T y, T w, T h)
				: X(x), Y(y), Width(w), Height(h)
			{
			}

			AABB(T w, T h)
				: AABB(0, 0, w, h)
			{
			}
		};

		typedef AABB<int> AABBi;
		typedef AABB<float> AABBf;
		typedef AABB<double> AABBd;
	}
}