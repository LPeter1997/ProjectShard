#include "GUIContainer.h"

namespace Shard
{
	namespace GUI
	{
		GUIContainer::GUIContainer(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector2f& size)
			: GUIComponent(parent, pos, size)
		{
		}

		GUIContainer::GUIContainer(const Maths::Vector2f& pos, const Maths::Vector2f& size)
			: GUIComponent(pos, size)
		{
		}

		GUIContainer::~GUIContainer()
		{
			for (GUIComponent* c : m_Children)
				delete c;
		}
	}
}