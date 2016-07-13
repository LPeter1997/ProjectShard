#include <cmath>
#include "NarrowPhase.h"

namespace Shard
{
	namespace Physics
	{
		Mainfold::Mainfold(RigidBody* a, RigidBody* b)
			: A(a), B(b)
		{
		}

		void Mainfold::PreCompute()
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
			}
		}
	}
}