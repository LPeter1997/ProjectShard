#include "ImpulseIntegrator.h"
#include <iostream>

namespace Shard
{
	namespace Physics
	{
		namespace ImpulseIntegrator
		{
			static inline float pythagoreanSolve(float a, float b)
			{
				return std::sqrtf(a * a + b * b);
			}

			static inline bool equal(float a, float b)
			{
				return std::fabsf(a - b) <= 0.0001f;
			}

			void ApplyImpulse(Mainfold* mf)
			{
				RigidBody* A = mf->A;
				RigidBody* B = mf->B;

				if (equal(A->BodyMass.InvMass + B->BodyMass.InvMass, 0.0f))
				{
					InfiniteMassCorrection(mf);
					return;
				}

				for (uint i = 0; i < mf->ContactCount; i++)
				{
					Maths::Vector2f ra = mf->Contacts[i] - A->Position;
					Maths::Vector2f rb = mf->Contacts[i] - B->Position;

					// Relative vel
					Maths::Vector2f relativeVel = B->Velocity + Maths::Vector2f::CrossProduct(B->AngularVelocity, rb) -
												A->Velocity - Maths::Vector2f::CrossProduct(A->AngularVelocity, ra);

					// Relative velocity along the normal
					float contactVel = Maths::Vector2f::DotProduct(relativeVel, mf->Normal);

					// Separating
					if (contactVel > 0)
						return;

					float raCrossN = Maths::Vector2f::CrossProduct(ra, mf->Normal);
					float rbCrossN = Maths::Vector2f::CrossProduct(rb, mf->Normal);
					float invMassSum = A->BodyMass.InvMass + B->BodyMass.InvMass +
									raCrossN * raCrossN * A->BodyMass.InvInertia +
									rbCrossN * rbCrossN * B->BodyMass.InvInertia;

					// Calculate impulse
					float j = -(1.0f + mf->E) * contactVel;
					j /= invMassSum;
					j /= (float)mf->ContactCount;

					// Apply impulse
					Maths::Vector2f impulse(j * mf->Normal.x, j * mf->Normal.y);
					A->ApplyImpulse(Maths::Vector2f(-impulse.x, -impulse.y), ra);
					B->ApplyImpulse(impulse, rb);

					// Friction impulse
					relativeVel = B->Velocity + Maths::Vector2f::CrossProduct(B->AngularVelocity, rb) -
								A->Velocity - Maths::Vector2f::CrossProduct(A->AngularVelocity, ra);

					float __dot = Maths::Vector2f::DotProduct(relativeVel, mf->Normal);
					Maths::Vector2f _dotted(__dot * mf->Normal.x, __dot * mf->Normal.y);
					Maths::Vector2f t = relativeVel - _dotted;
					t.Normalize();

					// j is tangent magnitude
					float jt = -Maths::Vector2f::DotProduct(relativeVel, t);
					jt /= invMassSum;
					jt /= (float)mf->ContactCount;

					// Don't appl,y tiny friction impulse
					if (equal(jt, 0.0f))
						return;

					// Coulomb's Law
					Maths::Vector2f tangentImpulse;
					if (std::fabsf(jt) < j * mf->SF)
						tangentImpulse = Maths::Vector2f(jt * t.x, jt * t.y);
					else
						tangentImpulse = Maths::Vector2f(-j * mf->DF * t.x, -j * mf->DF * t.y);

					// Apply friction impulse
					A->ApplyImpulse(Maths::Vector2f(-tangentImpulse.x, -tangentImpulse.y), ra);
					B->ApplyImpulse(tangentImpulse, rb);
				}
			}

			void PositionalCorrection(Mainfold* mf)
			{
				const float error = 0.05f;
				const float percent = 0.4f;
				float factor = std::fmaxf(mf->Penetration - error, 0.0f) / (mf->A->BodyMass.InvMass + mf->B->BodyMass.InvMass) * percent;
				Maths::Vector2f correction(factor * mf->Normal.x, factor * mf->Normal.y);

				mf->A->Position -= Maths::Vector2f(mf->A->BodyMass.InvMass * correction.x, mf->A->BodyMass.InvMass * correction.y);
				mf->B->Position += Maths::Vector2f(mf->B->BodyMass.InvMass * correction.x, mf->B->BodyMass.InvMass * correction.y);
			}

			void InfiniteMassCorrection(Mainfold* mf)
			{
				mf->A->Velocity.x = 0;
				mf->A->Velocity.y = 0;

				mf->B->Velocity.x = 0;
				mf->B->Velocity.y = 0;
			}
		}
	}
}