#pragma once

#include "Mainfold.h"

namespace Shard
{
	namespace Physics
	{
		namespace NarrowCollision
		{
			typedef bool (*NarrowCollisionFn)(Mainfold*);

			void Initialize();
			bool Collide(Mainfold* mainfold);

			bool CircleAndCircle(Mainfold* mainfold);
			bool PolygonAndPolygon(Mainfold* mainfold);
			bool PolygonAndCircle(Mainfold* mainfold);
			bool CircleAndPolygon(Mainfold* mainfold);
		}
	}
}