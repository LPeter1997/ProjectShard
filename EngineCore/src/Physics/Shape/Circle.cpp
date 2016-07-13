#include "Circle.h"

namespace Shard
{
	namespace Physics
	{
		Circle::Circle(const Maths::Vector2f& orig, float rad)
			: Shape(ShapeType::Circle), Origin(orig), Radius(rad)
		{
		}

		Circle::Circle(float rad)
			: Circle(Maths::Vector2f(0, 0), rad)
		{
		}
	}
}