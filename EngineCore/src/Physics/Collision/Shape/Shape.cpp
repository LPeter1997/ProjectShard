#include "Shape.h"

namespace Shard
{
	namespace Physics
	{
		Shape::Shape(ShapeType t)
			: Type(t), Transform(Maths::Matrix2f(1.0f))
		{
		}

		Shape::~Shape()
		{
		}
	}
}