#pragma once

#include <vector>
#include "Material.h"
#include "MassData.h"
#include "../Collision/Shape/Shape.h"
#include "../../Maths/Vector2.h"

namespace Shard
{
	namespace Physics
	{
		class Joint;

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
			// Array of joints
			std::vector<Joint*> Joints;

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
				AngularVelocity += BodyMass.InvInertia * Maths::Vector2f::CrossProduct(contact, impulse);
			}

			inline void ApplyImpulseInstant(const Maths::Vector2f& impulse, const Maths::Vector2f& contact)
			{
				Position += Maths::Vector2f(BodyMass.InvMass * impulse.x, BodyMass.InvMass * impulse.y);
				Orientation += BodyMass.InvInertia * Maths::Vector2f::CrossProduct(contact, impulse);
				SetOrientation(Orientation);
			}

			inline void SetOrientation(float radians)
			{
				Orientation = radians;
				BodyShape->SetOrientation(radians);
			}

			inline void AddJoint(Joint* jnt)
			{
				Joints.push_back(jnt);
			}

		private:
			static MassData ComputeMass(Shape* sh, const Material& mat);
		};
	}
}