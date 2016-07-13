#include "RigidBody.h"

namespace Shard
{
	namespace Physics
	{
		RigidBody::RigidBody(const Maths::Vector2f& pos, Shape* shape, const Material& mat)
			: Position(pos), BodyMaterial(mat), BodyMass(ComputeMass(shape, mat)), BodyShape(shape)
		{
		}

		MassData RigidBody::ComputeMass(const Shape* sh, const Material& mat)
		{
			return sh->ComputeMass(mat);
		}
	}
}