#pragma once

#include "../Types.h"
#include "../Maths/Vector2.h"
#include "../Maths/Vector3.h"

namespace Shard
{
	namespace Gfx
	{
		struct VertexData2D
		{
			Maths::Vector3f Position;
			uint Color;
			Maths::Vector2f UV;
			float TextureID;
		};
	}
}