#pragma once

#include "Joints\RevoluteJoint.h"

namespace Shard
{
	namespace Physics
	{
		namespace JointImpulse
		{
			void IntegrateJointForce(RevoluteJoint* joint);
		}
	}
}