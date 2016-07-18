#include "RevoluteJoint.h"

namespace Shard
{
	namespace Physics
	{
		RevoluteJoint::RevoluteJoint(RigidBody* a, RigidBody* b, const Maths::Vector2f& anchA, const Maths::Vector2f& anchB)
			: Joint(JointType::Revolute, a, b, anchA, anchB)
		{
		}

		RevoluteJoint::RevoluteJoint(RigidBody* a, RigidBody* b)
			: Joint(JointType::Revolute, a, b)
		{
		}
	}
}