#include "Joint.h"

namespace Shard
{
	namespace Physics
	{
		Joint::Joint(JointType type, RigidBody* a, RigidBody* b, const Maths::Vector2f& anchA, const Maths::Vector2f& anchB)
			: Type(type), A(a), B(b), AnchorPointA(anchA), AnchorPointB(anchB)
		{
		}

		Joint::Joint(JointType type, RigidBody* a, RigidBody* b)
			: Type(type), A(a), B(b)
		{
		}
	}
}