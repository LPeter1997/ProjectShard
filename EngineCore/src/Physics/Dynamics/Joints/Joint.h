#pragma once

#include "../RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		enum class JointType
		{
			Revolute,
			__Size__
		};

		struct Joint
		{
		public:
			JointType Type;
			RigidBody* A;
			RigidBody* B;
			Maths::Vector2f AnchorPointA;
			Maths::Vector2f AnchorPointB;

		public:
			Joint(JointType type, RigidBody* a, RigidBody* b, const Maths::Vector2f& anchA, const Maths::Vector2f& anchB);
			Joint(JointType type, RigidBody* a, RigidBody* b);
		};
	}
}