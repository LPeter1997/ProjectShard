#pragma once

#include "../Types.h"
#include "../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ColorUtils
		{
			inline uint RGBATo32Int(const Maths::Vector4f& color)
			{
						// RED //////////////////////	// GREEN /////////////////////	  // BLUE ///////////////////	 // ALPHA /////////////
				return (((int)(color.x * 255)) << 24) | (((int)(color.y * 255)) << 16) | (((int)(color.z * 255)) << 8) | ((int)(color.w * 255));
			}
		}
	}
}