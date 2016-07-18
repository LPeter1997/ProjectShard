#include "JointImpulse.h"

namespace Shard
{
	namespace Physics
	{
		namespace JointImpulse
		{
			void IntegrateJointForce(RevoluteJoint* joint)
			{
				RigidBody* A = joint->A;
				RigidBody* B = joint->B;

				Maths::Vector2f ancha = A->BodyShape->Transform * joint->AnchorPointA;
				Maths::Vector2f anchb = B->BodyShape->Transform * joint->AnchorPointB;

				Maths::Vector2f relativeVel = (B->Position + B->Velocity + anchb) - (A->Position + A->Velocity + ancha);

				B->ApplyImpulse(Maths::Vector2f(-relativeVel.x, -relativeVel.y), anchb);
				A->ApplyImpulse(relativeVel, ancha);
			}
		}
	}
}