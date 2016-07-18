#pragma once

#include "Joint.h"

namespace Shard
{
	namespace Physics
	{
		class RevoluteJoint : public Joint
		{
		public:
			RevoluteJoint(RigidBody* a, RigidBody* b, const Maths::Vector2f& anchA, const Maths::Vector2f& anchB);
			RevoluteJoint(RigidBody* a, RigidBody* b);
		};
	}
}