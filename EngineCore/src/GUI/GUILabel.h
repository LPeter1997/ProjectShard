#pragma once

#include <string>
#include "GUIComponent.h"

namespace Shard
{
	namespace GUI
	{
		class GUILabel : public GUIComponent
		{
		protected:
			std::string m_Text;
			const Gfx::FontAtlas& m_Font;

		public:
			GUILabel(GUIComponent* parent, const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const std::string& text);
			GUILabel(const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const std::string& text);

			inline void Render(Gfx::Renderer2D& renderer) override
			{
				renderer.DrawString(m_Position, m_Text, m_Font, 0xff000000);
			}
		};
	}
}