#include "MassData.h"

namespace Shard
{
	namespace Physics
	{
		MassData::MassData(float mass, float in)
		{
			if (mass == 0)
				InvMass = 0;
			else
				InvMass = 1.0f / mass;

			if (in == 0)
				InvInertia = 0.0f;
			else
				InvInertia = 1.0f / in;
		}

		MassData::MassData(float mass)
			: MassData(mass, 0.0f)
		{
		}

		MassData::MassData()
			: MassData(0.0f, 0.0f)
		{
		}
	}
}