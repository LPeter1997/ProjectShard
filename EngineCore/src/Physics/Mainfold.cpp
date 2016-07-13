#include <cmath>
#include "NarrowPhase.h"

namespace Shard
{
	namespace Physics
	{
		Mainfold::Mainfold(RigidBody* a, RigidBody* b)
			: A(a), B(b), ContactCount(0)
		{
		}

		void Mainfold::PreCompute(float delta, const Maths::Vector2f& gravity)
		{
			// Restitution
			E = std::fminf(A->BodyMaterial.Restitution, B->BodyMaterial.Restitution);

			// Static and dynamic friction
			SF = std::sqrtf(A->BodyMaterial.StaticFriction * B->BodyMaterial.StaticFriction);
			DF = std::sqrtf(A->BodyMaterial.DynamicFriction * B->BodyMaterial.DynamicFriction);

			for (uint i = 0; i < ContactCount; i++)
			{
				Maths::Vector2f ra = Contacts[i] - A->Position;
				Maths::Vector2f rb = Contacts[i] - B->Position;

				Maths::Vector2f rv = B->Velocity + Maths::Vector2f::CrossProduct(B->AngularVelocity, rb) -
									A->Velocity - Maths::Vector2f::CrossProduct(A->AngularVelocity, ra);

				// Resting collision
				Maths::Vector2f grav(delta * gravity.x, delta * gravity.y);
				if ((rv.x * rv.x + rv.y * rv.y) < (grav.x * grav.x + grav.y * grav.y) + 0.0001f)
					E = 0.0f;
			}
		}
	}
}