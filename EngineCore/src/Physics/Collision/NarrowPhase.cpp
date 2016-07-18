#include <cmath>
#include "NarrowPhase.h"
#include "Shape\Circle.h"
#include "Shape\Polygon.h"
#include "../../Types.h"

namespace Shard
{
	namespace Physics
	{
		namespace NarrowCollision
		{
			static NarrowCollisionFn CollisionFunctionLookup[(uint)ShapeType::__Size__ * (uint)ShapeType::__Size__];

			constexpr static inline uint LookupPos(ShapeType p1, ShapeType p2)
			{
				return (uint)p1 + ((uint)p2 * (uint)ShapeType::__Size__);
			}

			void Initialize()
			{
				CollisionFunctionLookup[LookupPos(ShapeType::Circle, ShapeType::Circle)] = CircleAndCircle;
				CollisionFunctionLookup[LookupPos(ShapeType::Polygon, ShapeType::Circle)] = PolygonAndCircle;
				CollisionFunctionLookup[LookupPos(ShapeType::Circle, ShapeType::Polygon)] = CircleAndPolygon;
				CollisionFunctionLookup[LookupPos(ShapeType::Polygon, ShapeType::Polygon)] = PolygonAndPolygon;
			}

			bool Collide(Mainfold* mainfold)
			{
				return CollisionFunctionLookup[(uint)mainfold->A->BodyShape->Type + ((uint)mainfold->B->BodyShape->Type * (uint)ShapeType::__Size__)](mainfold);
			}

			bool CircleAndCircle(Mainfold* mainfold)
			{
				// Shortcut for shapes
				Circle* A = (Circle*)mainfold->A->BodyShape;
				Circle* B = (Circle*)mainfold->B->BodyShape;

				Maths::Vector2f normal = mainfold->B->Position - mainfold->A->Position;

				float distSqr = normal.x * normal.x + normal.y * normal.y;
				float radius = A->Radius + B->Radius;

				// No contact
				if (distSqr >= radius * radius)
				{
					return false;
				}

				float distance = std::sqrtf(distSqr);
				if (distance == 0)
				{
					// Concentric
					mainfold->Penetration = A->Radius;
					mainfold->Normal = Maths::Vector2f(1, 0);
					mainfold->Contacts[0] = mainfold->A->Position;
					mainfold->ContactCount = 1;
					return true;
				}
				else
				{
					mainfold->Penetration = radius - distance;
					mainfold->Normal = Maths::Vector2f(normal.x / distance, normal.y / distance);
					mainfold->Contacts[0] = Maths::Vector2f(mainfold->Normal.x * A->Radius, mainfold->Normal.y * A->Radius) + mainfold->A->Position;
					mainfold->ContactCount = 1;
					return true;
				}
			}

			bool CircleAndPolygon(Mainfold* mainfold)
			{
				// Shortcut for shapes
				Circle* A = (Circle*)mainfold->A->BodyShape;
				Polygon* B = (Polygon*)mainfold->B->BodyShape;

				Maths::Vector2f center = mainfold->A->Position;
				// Transpose circle to polygon's model space
				center = B->Transform.Transposed() * (center - mainfold->B->Position);

				// Edge with minimum penetration
				float separation = -FLT_MAX;
				uint faceNormal = 0;
				for (uint i = 0; i < B->Vertices.size(); i++)
				{
					float s = Maths::Vector2f::DotProduct(B->Normals.at(i), center - B->Vertices.at(i));

					if (s > A->Radius)
						return false;

					if (s > separation)
					{
						separation = s;
						faceNormal = i;
					}
				}

				//Check if center is in polygon
				if (separation < 0.0001f)
				{
					Maths::Vector2f _norm = B->Transform * B->Normals.at(faceNormal);
					mainfold->Normal = Maths::Vector2f(-_norm.x, -_norm.y);
					mainfold->Contacts[0] = Maths::Vector2f(A->Radius * mainfold->Normal.x, A->Radius * mainfold->Normal.y) + mainfold->A->Position;
					mainfold->ContactCount = 1;
					mainfold->Penetration = A->Radius;
					return true;
				}

				// Face's vertices
				Maths::Vector2f v1 = B->Vertices.at(faceNormal);
				Maths::Vector2f v2 = B->Vertices.at(faceNormal + 1 < B->Vertices.size() ? faceNormal + 1 : 0);

				float dot1 = Maths::Vector2f::DotProduct(center - v1, v2 - v1);
				float dot2 = Maths::Vector2f::DotProduct(center - v2, v1 - v2);
				mainfold->Penetration = A->Radius - separation;

				if (dot1 <= 0.0f)
				{
					// Closest to v1
					Maths::Vector2f _dist = center - v1;
					if ((_dist.x * _dist.x + _dist.y * _dist.y) > A->Radius * A->Radius)
						return false;

					Maths::Vector2f n = v1 - center;
					n = B->Transform * n;
					n.Normalize();
					mainfold->Normal = n;
					v1 = B->Transform * v1 + mainfold->B->Position;
					mainfold->Contacts[0] = v1;
					mainfold->ContactCount = 1;
					return true;
				}
				else if (dot2 <= 0.0f)
				{
					// Closest to v2
					Maths::Vector2f _dist = center - v2;
					if ((_dist.x * _dist.x + _dist.y * _dist.y) > A->Radius * A->Radius)
						return false;

					Maths::Vector2f n = v2 - center;
					v2 = B->Transform * v2 + mainfold->B->Position;
					mainfold->Contacts[0] = v2;
					mainfold->ContactCount = 1;
					n = B->Transform * n;
					n.Normalize();
					mainfold->Normal = n;
					return true;
				}
				else
				{
					// Closest to face
					Maths::Vector2f n = B->Normals.at(faceNormal);
					if (Maths::Vector2f::DotProduct(center - v1, n) > A->Radius)
						return false;

					n = B->Transform * n;
					mainfold->Normal = Maths::Vector2f(-n.x, -n.y);
					mainfold->Contacts[0] = Maths::Vector2f(A->Radius * mainfold->Normal.x, A->Radius * mainfold->Normal.y) + mainfold->A->Position;
					mainfold->ContactCount = 1;
					return true;
				}
			}

			bool PolygonAndCircle(Mainfold* mainfold)
			{
				// Swap
				RigidBody* tmp = mainfold->A;
				mainfold->A = mainfold->B;
				mainfold->B = tmp;

				bool r = CircleAndPolygon(mainfold);
				mainfold->Normal = Maths::Vector2f(-mainfold->Normal.x, -mainfold->Normal.y);
				
				// Swap back
				tmp = mainfold->A;
				mainfold->A = mainfold->B;
				mainfold->B = tmp;

				return r;
			}

			static float findAxisLeastPenetration(uint& faceIndex, RigidBody* a, RigidBody* b)
			{
				Polygon* A = (Polygon*)a->BodyShape;
				Polygon* B = (Polygon*)b->BodyShape;

				float bestDistance = -FLT_MAX;
				uint bestIndex = 0;
				Maths::Matrix2f buT = B->Transform.Transposed();

				for (uint i = 0; i < A->Vertices.size(); i++)
				{
					Maths::Vector2f n = A->Normals.at(i);
					Maths::Vector2f nw = A->Transform * n;

					// Transform face normal to B's model space
					n = buT * nw;

					// Retrieve support point from B along -n
					Maths::Vector2f s = B->GetSupport(Maths::Vector2f(-n.x, -n.y));

					// Retrieve vertex on face from A, transform to B's model space
					Maths::Vector2f v = A->Vertices.at(i);
					v = A->Transform * v + a->Position;
					v -= b->Position;
					v = buT * v;

					// Compute penetration distance in B's model space
					float d = Maths::Vector2f::DotProduct(n, s - v);

					// Store greatest
					if (d > bestDistance)
					{
						bestDistance = d;
						bestIndex = i;
					}
				}

				faceIndex = bestIndex;
				return bestDistance;
			}

			static void findIncidentFace(Maths::Vector2f* v, Polygon* refPoly, RigidBody* incBody, Polygon* incPoly, uint referenceIndex)
			{
				Maths::Vector2f referenceNormal = refPoly->Normals.at(referenceIndex);

				// Calculate normal
				referenceNormal = refPoly->Transform * referenceNormal;
				referenceNormal = incPoly->Transform.Transposed() * referenceNormal;

				// Find most non-normal face
				uint incidentFace = 0;
				float minDot = FLT_MAX;
				for (uint i = 0; i < incPoly->Vertices.size(); i++)
				{
					float dot = Maths::Vector2f::DotProduct(referenceNormal, incPoly->Normals.at(i));
					if (dot < minDot)
					{
						minDot = dot;
						incidentFace = i;
					}
				}

				v[0] = incPoly->Transform * incPoly->Vertices.at(incidentFace) + incBody->Position;
				incidentFace = incidentFace + 1 < incPoly->Vertices.size() ? incidentFace + 1 : 0;
				v[1] = incPoly->Transform * incPoly->Vertices.at(incidentFace) + incBody->Position;
			}

			static uint Clip(Maths::Vector2f n, float c, Maths::Vector2f* face)
			{
				uint sp = 0;
				Maths::Vector2f out[2] =
				{
					face[0], face[1]
				};

				// Retrieve distances from each endpoint to the line
				float d1 = Maths::Vector2f::DotProduct(n, face[0]) - c;
				float d2 = Maths::Vector2f::DotProduct(n, face[1]) - c;

				if (d1 <= 0.0f) out[sp++] = face[0];
				if (d2 <= 0.0f) out[sp++] = face[1];

				if (d1 * d2 < 0.0f)
				{
					float alpha = d1 / (d1 - d2);
					Maths::Vector2f _dif = (face[1] - face[0]);
					out[sp++] = face[0] + Maths::Vector2f(alpha * _dif.x, alpha * _dif.y);
				}

				face[0] = out[0];
				face[1] = out[1];

				return sp;
			}

			inline bool biasGreaterThan(float a, float b)
			{
				const float biasRelative = 0.95f;
				const float biasAbsolute = 0.01f;
				return a >= b * biasRelative + a * biasAbsolute;
			}

			bool PolygonAndPolygon(Mainfold* mainfold)
			{
				// Shortcut for shapes
				Polygon* A = (Polygon*)mainfold->A->BodyShape;
				Polygon* B = (Polygon*)mainfold->B->BodyShape;

				uint faceA;
				float penetrationA = findAxisLeastPenetration(faceA, mainfold->A, mainfold->B);
				if (penetrationA >= 0.0f)
					return false;

				uint faceB;
				float penetrationB = findAxisLeastPenetration(faceB, mainfold->B, mainfold->A);
				if (penetrationB >= 0.0f)
					return false;

				uint referenceIndex;
				bool flip;

				Polygon* refPoly;
				RigidBody* refBody;
				Polygon* incPoly;
				RigidBody* incBody;

				if (biasGreaterThan(penetrationA, penetrationB))
				{
					refPoly = A;
					refBody = mainfold->A;
					incPoly = B;
					incBody = mainfold->B;
					referenceIndex = faceA;
					flip = false;
				}
				else
				{
					refPoly = B;
					refBody = mainfold->B;
					incPoly = A;
					incBody = mainfold->A;
					referenceIndex = faceB;
					flip = true;
				}

				Maths::Vector2f incidentFace[2];
				findIncidentFace(incidentFace, refPoly, incBody, incPoly, referenceIndex);

				// Setup reference face verts
				Maths::Vector2f v1 = refPoly->Vertices.at(referenceIndex);
				referenceIndex = referenceIndex + 1 < refPoly->Vertices.size() ? referenceIndex + 1 : 0;
				Maths::Vector2f v2 = refPoly->Vertices.at(referenceIndex);

				// Transform verts to world space
				v1 = refPoly->Transform * v1 + refBody->Position;
				v2 = refPoly->Transform * v2 + refBody->Position;

				// Calculate reference face side normal in world space
				Maths::Vector2f sidePlaneNormal = v2 - v1;
				sidePlaneNormal.Normalize();

				// Orthogonalize
				Maths::Vector2f refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

				float refC = Maths::Vector2f::DotProduct(refFaceNormal, v1);
				float negSide = -Maths::Vector2f::DotProduct(sidePlaneNormal, v1);
				float posSide = Maths::Vector2f::DotProduct(sidePlaneNormal, v2);

				// Clip incident face to reference face side planes
				if (Clip(Maths::Vector2f(-sidePlaneNormal.x, -sidePlaneNormal.y), negSide, incidentFace) < 2)
					return false;

				if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
					return false;

				// Flip
				mainfold->Normal = flip ? Maths::Vector2f(-refFaceNormal.x, -refFaceNormal.y) : refFaceNormal;

				// Keep points behind the reference face
				uint cp = 0;
				float separation = Maths::Vector2f::DotProduct(refFaceNormal, incidentFace[0]) - refC;
				if (separation <= 0.0f)
				{
					mainfold->Contacts[cp++] = incidentFace[0];
					mainfold->Penetration = -separation;
				}
				else
					mainfold->Penetration = 0;

				separation = Maths::Vector2f::DotProduct(refFaceNormal, incidentFace[1]) - refC;
				if (separation <= 0.0f)
				{
					mainfold->Contacts[cp++] = incidentFace[1];
					mainfold->Penetration -= separation;

					// Average penetration
					mainfold->Penetration /= (float)cp;
				}

				mainfold->ContactCount = cp;
				return cp > 0;
			}
		}
	}
}