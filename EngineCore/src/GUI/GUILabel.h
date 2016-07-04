#pragma once

#include <string>
#include "GUIComponent.h"
#include "../Gfx/ColorUtils.h"
#include "../Gfx/FontMetrics.h"

namespace Shard
{
	namespace GUI
	{
		class GUILabel : public GUIComponent
		{
		protected:
			std::string m_Text;
			const Gfx::FontAtlas& m_Font;
			uint m_Color;
			Gfx::TextMeasurement m_Measurement;

		public:
			GUILabel(GUIComponent* parent, const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const Maths::Vector4f& color, const std::string& text);
			GUILabel(const Maths::Vector2f& pos, const Gfx::FontAtlas& font, const Maths::Vector4f& color, const std::string& text);

			inline void Render(Gfx::Renderer2D& renderer) override
			{
				renderer.DrawString(m_Position, m_Measurement, m_Color);
			}

			inline void SetText(const std::string& str)
			{
				m_Text = str;
				m_Measurement = m_Font.GetFontMetrics().MeasureText(m_Text);
			}
		};
	}
}