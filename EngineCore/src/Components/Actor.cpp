#include "Actor.h"

namespace Shard
{
	namespace Components
	{
		Actor::Actor(const Maths::Vector3f& pos)
		{
			m_Transform.SetPosition(pos);
		}

		Actor::~Actor()
		{
			for (Component* c : m_Components)
				delete c;
		}
	}
}