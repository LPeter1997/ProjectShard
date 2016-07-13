/*#pragma once

#include <vector>
#include "RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		namespace BroadCollision
		{
			struct ColliderPair
			{
			public:
				RigidBody* A;
				RigidBody* B;

			public:
				ColliderPair(RigidBody* a, RigidBody* b)
					: A(a), B(b)
				{
				}
			};

			std::vector<ColliderPair> GenerateColliderPairs(std::vector<RigidBody*>& bodies);
		}
	}
}*/