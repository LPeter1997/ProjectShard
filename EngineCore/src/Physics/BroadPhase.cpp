/*
#include "BroadPhase.h"
#include "Shape\AABB.h"
#include "PrimitiveIntersection.h"
#include <iostream>

namespace Shard
{
	namespace Physics
	{
		namespace BroadCollision
		{
			std::vector<ColliderPair> GenerateColliderPairs(std::vector<RigidBody*>& bodies)
			{
				std::vector<ColliderPair> pairs;

				for (auto i = bodies.begin(); i != bodies.end(); i++)
				{
					RigidBody* A = *i;
					AABB as = A->BodyShape->ComputeAABB();
					for (auto j = i + 1; j != bodies.end(); j++)
					{
						RigidBody* B = *j;

						// Infinite masses, no collision
						if (A->InvMass == 0.0f && B->InvMass == 0.0f)
							continue;

						AABB bs = B->BodyShape->ComputeAABB();

						if (PrimitiveIntersection::AABBandAABB(as, bs))
						{
							pairs.push_back(ColliderPair(A, B));
						}
					}
				}

				return pairs;
			}
		}
	}
}*/