#pragma once

#include "../../Dynamics/Material.h"
#include "../../Dynamics/MassData.h"
#include "../../../Maths/AABB.h"
#include "../../../Maths/Matrix.h"

namespace Shard
{
	namespace Physics
	{
		enum class ShapeType
		{
			Circle, Polygon,
			__Size__
		};

		struct Shape
		{
		public:
			ShapeType Type;
			Maths::Matrix2f Transform;

		public:
			Shape(ShapeType t);
			virtual ~Shape();

			virtual MassData ComputeMass(const Material& mat) = 0;
			
			inline void SetOrientation(float radians)
			{
				Transform = Maths::Matrix2f::Rotation2D(radians);
			}
		};
	}
}