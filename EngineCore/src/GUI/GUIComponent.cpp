#include "GUIComponent.h"

namespace Shard
{
	namespace GUI
	{
		GUIComponent::GUIComponent(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector2f& size)
			: m_Parent(parent), m_Position(Maths::Vector3f(pos.x, pos.y, 0)), m_Size(size)
		{
		}

		GUIComponent::GUIComponent(const Maths::Vector2f& pos, const Maths::Vector2f& size)
			: GUIComponent(nullptr, pos, size)
		{
		}

		GUIComponent::~GUIComponent()
		{
		}
	}
}