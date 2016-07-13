#pragma once

#include "RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		namespace ForceIntegrator
		{
			inline void IntegrateForces(RigidBody* body, const Maths::Vector2f& gravity, float delta)
			{
				if (body->BodyMass.InvMass == 0)
					return;

				Maths::Vector2f f(body->BodyMass.InvMass * body->Force.x, body->BodyMass.InvMass * body->Force.y);
				f += gravity;
				body->Velocity += Maths::Vector2f((delta / 2.0f) * f.x, (delta / 2.0f) * f.y);
				body->AngularVelocity += body->Torque * body->BodyMass.InvInertia * (delta / 2.0f);
			}

			inline void IntegrateVelocity(RigidBody* body, const Maths::Vector2f& gravity, float delta)
			{
				if (body->BodyMass.InvMass == 0.0f)
					return;

				body->Position += Maths::Vector2f(delta * body->Velocity.x, delta * body->Velocity.y);
				body->Orientation += body->AngularVelocity * delta;
				body->SetOrientation(body->Orientation);
				IntegrateForces(body, gravity, delta);
			}
		}
	}
}