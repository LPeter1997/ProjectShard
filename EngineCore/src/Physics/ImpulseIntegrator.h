#pragma once

#include "NarrowPhase.h"

namespace Shard
{
	namespace Physics
	{
		namespace ImpulseIntegrator
		{
			void ApplyImpulse(Mainfold* mf);
			void PositionalCorrection(Mainfold* mf);
			void InfiniteMassCorrection(Mainfold* mf);
		}
	}
}