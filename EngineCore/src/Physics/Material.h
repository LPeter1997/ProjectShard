#pragma once

namespace Shard
{
	namespace Physics
	{
		struct Material
		{
		public:
			float Density;
			float Restitution;

			float StaticFriction;
			float DynamicFriction;

		public:
			Material(float dens, float res, float sfr, float dfr);
		};
	}
}