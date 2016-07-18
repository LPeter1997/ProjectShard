#pragma once

#include "../../Types.h"
#include "../Dynamics/RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		struct Mainfold
		{
		public:
			RigidBody* A;
			RigidBody* B;

			float Penetration;
			Maths::Vector2f Normal;
			Maths::Vector2f Contacts[2];
			uint ContactCount;

			float E; // Mixed restitution
			float SF; // Mixed static friction
			float DF; // Mixed dynamic friction

		public:
			Mainfold(RigidBody* a, RigidBody* b);

			void PreCompute(float delta, const Maths::Vector2f& gravity);
		};
	}
}