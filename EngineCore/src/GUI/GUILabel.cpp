#include "GUILabel.h"

namespace Shard
{
	namespace GUI
	{
		GUILabel::GUILabel(GUIComponent* parent, const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const std::string& text)
			: GUIComponent(parent, pos, Maths::Vector2f(0, 0)), m_Font(font), m_Text(text)
		{
		}

		GUILabel::GUILabel(const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const std::string& text)
			: GUIComponent(pos, Maths::Vector2f(0, 0)), m_Font(font), m_Text(text)
		{
		}
	}
}