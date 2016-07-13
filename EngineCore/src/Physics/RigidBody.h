#pragma once

#include "Shape\Shape.h"
#include "Material.h"
#include "MassData.h"
#include "../Maths/Vector2.h"

namespace Shard
{
	namespace Physics
	{
		class RigidBody
		{
		public:
			Shape* BodyShape;
			Material BodyMaterial;
			MassData BodyMass;

			// Linear
			Maths::Vector2f Position;
			Maths::Vector2f Velocity;
			Maths::Vector2f Force;
			// Angular
			float Orientation;
			float AngularVelocity;
			float Torque;

		public:
			RigidBody(const Maths::Vector2f& pos, Shape* shape, const Material& mat);

			inline void SetStatic()
			{
				BodyMass.InvMass = 0;
				BodyMass.InvInertia = 0;
			}

			inline void ApplyForce(const Maths::Vector2f& f)
			{
				Force += f;
			}

			inline void ApplyImpulse(const Maths::Vector2f& impulse, const Maths::Vector2f& contact)
			{
				Velocity += Maths::Vector2f(BodyMass.InvMass * impulse.x, BodyMass.InvMass * impulse.y);
			}

			inline void SetOrientation(float radians)
			{
				Orientation = radians;
				//BodyShape->SetOrientation(radians);
			}

		private:
			static MassData ComputeMass(const Shape* sh, const Material& mat);
		};
	}
}