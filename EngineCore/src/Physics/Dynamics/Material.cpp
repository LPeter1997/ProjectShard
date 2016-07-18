#include "Material.h"

namespace Shard
{
	namespace Physics
	{
		Material::Material(float dens, float res, float sfr, float dfr)
			: Density(dens), Restitution(res), StaticFriction(sfr), DynamicFriction(dfr)
		{
		}
	}
}