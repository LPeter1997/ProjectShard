#include "Component.h"

namespace Shard
{
	namespace Components
	{
		Component::Component(Actor& actor)
			: m_Actor(actor)
		{
		}

		Component::~Component()
		{
		}
	}
}