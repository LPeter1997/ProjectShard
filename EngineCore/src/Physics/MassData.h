#pragma once

namespace Shard
{
	namespace Physics
	{
		struct MassData
		{
		public:
			float InvMass;
			float Inertia;
			float InvInertia;

		public:
			MassData(float mass, float in);
			MassData(float mass);
			MassData();
		};
	}
}