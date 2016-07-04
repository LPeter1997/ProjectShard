#pragma once

#include "../Maths/Vector3.h"
#include "Component.h"

namespace Shard
{
	namespace Components
	{
		struct Transform
		{
			Maths::Vector3f Position;
			Maths::Vector3f Scale;
			Maths::Vector3f Rotation;
		};
	}
}