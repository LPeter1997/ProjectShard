#pragma once

#include <vector>
#include "../../../Maths/Vector2.h"
#include "Shape.h"

namespace Shard
{
	namespace Physics
	{
		struct Polygon : public Shape
		{
		public:
			std::vector<Maths::Vector2f> Vertices;
			std::vector<Maths::Vector2f> Normals;

		public:
			Polygon();

			void SetBox(float w, float h);
			void SetVertices(const std::vector<Maths::Vector2f>& polys);
			Maths::Vector2f GetSupport(const Maths::Vector2f& dir);

			MassData ComputeMass(const Material& mat) override;
		};
	}
}