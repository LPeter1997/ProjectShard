#pragma once

#include <cmath>
#include "Constants.h"

namespace Shard
{
	namespace Maths
	{
		inline double ToRadians(double degrees)
		{
			return degrees * (Constants::Pi / 180.0);
		}
	}
}