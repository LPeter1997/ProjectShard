#pragma once

#include "Shape.h"
#include "../../../Maths/Vector2.h"
#include "../../../Maths/Constants.h"

namespace Shard
{
	namespace Physics
	{
		struct Circle : public Shape
		{
		public:
			float Radius;

		public:
			Circle(float rad);

			inline MassData ComputeMass(const Material& mat) override
			{
				float mass = (Radius * Radius * Maths::Constants::Pi) * mat.Density;
				float in = mass * Radius * Radius;
				return MassData(mass, in);
			}
		};
	}
}