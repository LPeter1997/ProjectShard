#include "Shape.h"

namespace Shard
{
	namespace Physics
	{
		Shape::Shape(ShapeType t)
			: Type(t)
		{
		}

		Shape::~Shape()
		{
		}
	}
}