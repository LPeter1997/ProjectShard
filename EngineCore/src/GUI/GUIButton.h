#pragma once

#include "GUIContainer.h"
#include "GUILabel.h"
#include "../Input/Mouse.h"

namespace Shard
{
	namespace GUI
	{
		class GUIButton : public GUIContainer
		{
		protected:
			uint m_Color;
			const Maths::Vector2d& m_MousePosition;
			GUILabel* m_Label;
			float m_Padding;
			bool m_MouseOver;

		public:
			GUIButton(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector4f& color, GUILabel* label);
			GUIButton(const Maths::Vector2f& pos, const Maths::Vector4f& color, GUILabel* label);

			inline void Update(float delta) override
			{
				m_MouseOver = (m_Position.x <= m_MousePosition.x && m_Position.x + m_Size.x >= m_MousePosition.x)
					&& (m_Position.y <= m_MousePosition.y && m_Position.y + m_Size.y >= m_MousePosition.y);
				GUIContainer::Update(delta);
			}

			inline void Render(Gfx::Renderer2D& renderer) override
			{
				uint col = m_Color;
				if (m_MouseOver)
				{
					if (Input::Mouse::IsButtonDown(Input::Buttons::Left))
						col -= 0x00000022;
					else
						col += 0x00222222;
				}
				renderer.Draw(m_Position, m_Size, col);
				GUIContainer::Render(renderer);
			}
		};
	}
}