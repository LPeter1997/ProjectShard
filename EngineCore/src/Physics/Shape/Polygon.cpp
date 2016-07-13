#include "Polygon.h"
#include "../../Types.h"

namespace Shard
{
	namespace Physics
	{
		Polygon::Polygon()
			: Shape(ShapeType::Polygon)
		{
		}

		void Polygon::SetBox(float w, float h)
		{
			Vertices.clear();
			Normals.clear();

			float hw = w / 2.0f;
			float hh = h / 2.0f;

			Vertices.push_back(Maths::Vector2f(-hw, -hh));
			Vertices.push_back(Maths::Vector2f(hw, -hh));
			Vertices.push_back(Maths::Vector2f(hw, hh));
			Vertices.push_back(Maths::Vector2f(-hw, hh));

			Normals.push_back(Maths::Vector2f(0, -1));
			Normals.push_back(Maths::Vector2f(1, 0));
			Normals.push_back(Maths::Vector2f(0, 1));
			Normals.push_back(Maths::Vector2f(-1, 0));
		}

		void Polygon::SetVertices(const std::vector<Maths::Vector2f>& polys)
		{
			Vertices.clear();
			Normals.clear();

			uint rightMost = 0;
			float rightMostX = polys.at(0).x;
			for (uint i = 1; i < polys.size(); i++)
			{
				float x = polys.at(i).x;
				if (x > rightMostX)
				{
					rightMostX = x;
					rightMost = i;
				}
				else if (x == rightMostX)
				{
					// Most negative y
					if (polys.at(i).y < polys.at(rightMost).y)
						rightMost = i;
				}
			}

			uint *hull = new uint[polys.size()];
			uint outCount = 0;
			uint indexHull = rightMost;

			for (;;)
			{
				hull[outCount] = indexHull;

				// Search for next index that wraps around the hull
				uint nextHullIndex = 0;
				for (uint i = 1; i < polys.size(); i++)
				{
					if (nextHullIndex == indexHull)
					{
						nextHullIndex = i;
						continue;
					}

					Maths::Vector2f e1 = polys.at(nextHullIndex) - polys.at(hull[outCount]);
					Maths::Vector2f e2 = polys.at(i) - polys.at(hull[outCount]);
					float c = Maths::Vector2f::CrossProduct(e1, e2);
					if (c < 0.0f)
						nextHullIndex = i;

					if (c == 0.0f && ((e2.x * e2.x + e2.y * e2.y) > (e1.x * e1.x + e1.y * e1.y)))
						nextHullIndex = i;
				}

				outCount++;
				indexHull = nextHullIndex;

				if (nextHullIndex == rightMost)
				{
					break;
				}
			}

			// Copy vertices
			for (uint i = 0; i < outCount; i++)
				Vertices.push_back(polys.at(hull[i]));

			// Compute normals
			for (uint i = 0; i < Vertices.size(); i++)
			{
				uint j = i + 1 < Vertices.size() ? i + 1 : 0;
				Maths::Vector2f face = Vertices.at(j) - Vertices.at(i);

				Maths::Vector2f norm(face.y, -face.x);
				norm.Normalize();
				Normals.push_back(norm);
			}

			delete hull;
		}

		MassData Polygon::ComputeMass(const Material& mat)
		{
			Maths::Vector2f centroid(0, 0);
			float area = 0.0f;
			float I = 0.0f;

			const float kInv3 = 1.0f / 3.0f;

			for (uint i = 0; i < Vertices.size(); i++)
			{
				// Triangle verts (third as [0, 0])
				Maths::Vector2f p1(Vertices.at(i));
				Maths::Vector2f p2(Vertices.at((i + 1 < Vertices.size()) ? (i + 1) : 0));

				float D = Maths::Vector2f::CrossProduct(p1, p2);
				float triangleArea = 0.5f * D;

				area += triangleArea;

				// Weight centroid average
				float _wfactor = triangleArea * kInv3;
				Maths::Vector2f _sum = p1 + p2;
				centroid += Maths::Vector2f(_wfactor * _sum.x, _wfactor * _sum.y);

				float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
				float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
				I += (0.25f * kInv3 * D) * (intx2 + inty2);
			}

			float areaInv = 1.0f / area;
			centroid = Maths::Vector2f(areaInv * centroid.x, areaInv * centroid.y);

			// Translate verts to centroid
			for (Maths::Vector2f& v : Vertices)
				v -= centroid;

			float mass = mat.Density * area;
			float in = I * mat.Density;

			return MassData(mass, in);
		}

		Maths::Vector2f Polygon::GetSupport(const Maths::Vector2f& dir)
		{
			float bestProjection = -FLT_MAX;
			Maths::Vector2f bestVertex;

			for (Maths::Vector2f& v : Vertices)
			{
				float projection = Maths::Vector2f::DotProduct(v, dir);
				if (projection > bestProjection)
				{
					bestVertex = v;
					bestProjection = projection;
				}
			}

			return bestVertex;
		}
	}
}