#pragma once

#include "Vector3.h"

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct Orientation
		{
			Vector3<T> Direction;
			Vector3<T> UpVector;

			Orientation(const Vector3<T>& up, const Vector3<T>& dir)
				: UpVector(up), Direction(dir)
			{
			}

			Orientation(const Vector3<T>& dir)
				: UpVector(Vector3<T>(0, 1, 0)), Direction(dir)
			{
			}

			Orientation()
				: UpVector(Vector3<T>(0, 1, 0)), Direction(Vector3<T>(0, 0, -1))
			{
			}
		};

		typedef Orientation<int> Orientationi;
		typedef Orientation<float> Orientationf;
		typedef Orientation<double> Orientationd;
	}
}