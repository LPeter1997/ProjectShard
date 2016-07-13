#pragma once

#include "../Material.h"
#include "../MassData.h"

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

		public:
			Shape(ShapeType t);
			virtual ~Shape();

			virtual MassData ComputeMass(const Material& mat) = 0;
			virtual void SetOrientation(float radians) { };
		};
	}
}