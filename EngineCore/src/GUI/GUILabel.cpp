#include "GUILabel.h"

namespace Shard
{
	namespace GUI
	{
		GUILabel::GUILabel(GUIComponent* parent, const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const Maths::Vector4f& color, const std::string& text)
			: m_Measurement(font.GetFontMetrics().MeasureText(text)), GUIComponent(parent, pos, Maths::Vector2f(0, 0)), m_Font(font), m_Text(text), m_Color(Gfx::ColorUtils::RGBATo32IntABGR(color))
		{
			m_Size = m_Measurement.Size;
		}

		GUILabel::GUILabel(const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const Maths::Vector4f& color, const std::string& text)
			: GUILabel(nullptr, pos, font, color, text)
		{
		}
	}
}