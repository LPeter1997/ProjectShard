#include "CollisionResolver.h"
#include <iostream>

namespace Shard
{
	namespace Physics
	{
		namespace CollisionResolver
		{
			static inline float pythagoreanSolve(float a, float b)
			{
				return std::sqrtf(a * a + b * b);
			}

			void ResolveCollision(NarrowCollision::Mainfold* mf)
			{
				// Shortcut for colliders
				RigidBody* A = mf->A;
				RigidBody* B = mf->B;

				Maths::Vector2f relativeVel = B->Velocity - A->Velocity;
				float velAlongNorm = relativeVel.Dot(mf->Normal);

				// The shapes are separating
				if (velAlongNorm > 0)
					return;

				// Could move this to Mainfold creation, would speed up things
				float e = std::fminf(A->BodyMaterial.Restitution, B->BodyMaterial.Restitution);

				// Impulse scalar
				float j = (-(1 + e) * velAlongNorm) / (A->InvMass + B->InvMass);

				// Apply impulse
				Maths::Vector2f impulse = Maths::Vector2f(j * mf->Normal.x, j * mf->Normal.y);
				A->Velocity -= Maths::Vector2f(A->InvMass * impulse.x, A->InvMass * impulse.y);
				B->Velocity += Maths::Vector2f(B->InvMass * impulse.x, B->InvMass * impulse.y);

				// Recalculate relative velocity
				relativeVel = B->Velocity - A->Velocity;

				// Friction
				Maths::Vector2f tangent = relativeVel - Maths::Vector2f(velAlongNorm * mf->Normal.x, velAlongNorm * mf->Normal.y);
				tangent.Normalize();

				float jt = -relativeVel.Dot(tangent);
				jt /= A->InvMass + B->InvMass;

				// Approximate mu0 (static friction)
				float mu = pythagoreanSolve(A->BodyMaterial.StaticFriction, B->BodyMaterial.StaticFriction);

				// Clamp magnitude (Coulomb's Law)
				Maths::Vector2f frictionImpulse;
				if (std::fabsf(jt) < j * mu)
				{
					frictionImpulse.x = jt * tangent.x;
					frictionImpulse.y = jt * tangent.y;
				}
				else
				{
					// Dynamic friction
					float dmu = pythagoreanSolve(A->BodyMaterial.DynamicFriction, B->BodyMaterial.DynamicFriction);
					frictionImpulse.x = -j * dmu * tangent.x;
					frictionImpulse.y = -j * dmu * tangent.y;
				}

				// Apply forces
				A->Velocity -= Maths::Vector2f(A->InvMass * frictionImpulse.x, A->InvMass * frictionImpulse.y);
				A->Velocity += Maths::Vector2f(B->InvMass * frictionImpulse.x, B->InvMass * frictionImpulse.y);
			}

			void PositionalCorrection(NarrowCollision::Mainfold* mf)
			{
				RigidBody* A = mf->A;
				RigidBody* B = mf->B;
				const float percentage = 0.2f;
				const float error = 0.01f;
				float factor = (std::fmaxf(mf->Penetration - error, 0.0f) / (A->InvMass + B->InvMass)) * percentage;
				Maths::Vector2f correction = Maths::Vector2f(factor * mf->Normal.x, factor * mf->Normal.y);
				A->Position -= Maths::Vector2f(A->InvMass * correction.x, A->InvMass * correction.y);
				B->Position += Maths::Vector2f(B->InvMass * correction.x, B->InvMass * correction.y);
			}
		}
	}
}