#include "JointImpulse.h"
#include <iostream>

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

				Maths::Vector2f relativeVel = B->Position + anchb + B->Velocity + Maths::Vector2f::CrossProduct(B->AngularVelocity, anchb) -
					A->Velocity - A->Position - ancha - Maths::Vector2f::CrossProduct(A->AngularVelocity, anchb);

				Maths::Vector2f relativePos = (B->Position + anchb) - (A->Position + ancha) - relativeVel;

				A->ApplyImpulse(relativeVel, ancha);
				B->ApplyImpulse(Maths::Vector2f(-relativeVel.x, -relativeVel.y), anchb);
			}
		}
	}
}