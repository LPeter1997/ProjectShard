#pragma once

#include "NarrowPhase.h"

namespace Shard
{
	namespace Physics
	{
		namespace CollisionResolver
		{
			void ResolveCollision(NarrowCollision::Mainfold* mf);
			void PositionalCorrection(NarrowCollision::Mainfold* mf);
		}
	}
}