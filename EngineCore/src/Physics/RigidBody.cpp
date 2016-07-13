#include "RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		RigidBody::RigidBody(const Maths::Vector2f& pos, Shape* shape, const Material& mat)
			: Position(pos), BodyMaterial(mat), BodyMass(ComputeMass(shape, mat)), BodyShape(shape),
			Velocity(Maths::Vector2f(0, 0)), Force(Maths::Vector2f(0, 0)),
			Orientation(0), Torque(0), AngularVelocity(0)
		{
		}

		MassData RigidBody::ComputeMass(Shape* sh, const Material& mat)
		{
			return sh->ComputeMass(mat);
		}
	}
}