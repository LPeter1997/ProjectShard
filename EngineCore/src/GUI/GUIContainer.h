#pragma once

#include <vector>
#include "GUIComponent.h"

namespace Shard
{
	namespace GUI
	{
		class GUIContainer : public GUIComponent
		{
		protected:
			std::vector<GUIComponent*> m_Children;

		public:
			GUIContainer(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector2f& size);
			GUIContainer(const Maths::Vector2f& pos, const Maths::Vector2f& size);

			virtual ~GUIContainer();

			inline void AddComponent(GUIComponent* c)
			{
				c->m_Parent = this;
				m_Children.push_back(c);
			}

			virtual inline void Update(float delta) override
			{
				for (GUIComponent* c : m_Children)
					c->Update(delta);
			}

			virtual inline void Render(Gfx::Renderer2D& renderer) override
			{
				for (GUIComponent* c : m_Children)
					c->Render(renderer);
			}
		};
	}
}