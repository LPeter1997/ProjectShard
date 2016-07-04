#include "FontMetrics.h"
#include "FontAtlas.h"

namespace Shard
{
	namespace Gfx
	{
		FontMetrics::FontMetrics(const FontAtlas& font)
			: m_Font(font)
		{
		}

		TextMeasurement FontMetrics::MeasureText(const std::string& text) const
		{
			float left = 0;
			float top = 0;
			float w = 0;
			float h = 0;

			if (text.size() > 0)
			{
				const CharacterData& cd = m_Font.GetCharacterData(text[0]);
				left = cd.Left;
				top = cd.Top + cd.Height;
				w = -cd.Left;
			}

			for (uint i = 0; i < text.size(); i++)
			{
				char c = text[i];

				const CharacterData& ch = m_Font.GetCharacterData(c);
				
				if (i == text.size() - 1)
					w += ch.Width + ch.Left;
				else
					w += ch.X_Advance;

				h = ch.Height > h ? ch.Height : h;

				left = left < ch.Left ? ch.Left : left;
				top = top < (ch.Top + ch.Height) ? (ch.Top + ch.Height) : top;
			}

			return TextMeasurement(m_Font, text, Maths::Vector2f(left, -top), Maths::Vector2f(w, h));
		}

		Maths::Vector2f FontMetrics::MeasureTextSize(const std::string& text) const
		{
			float w = 0;
			float h = 0;

			if (text.size() > 0)
			{
				const CharacterData& cd = m_Font.GetCharacterData(text[0]);
				w = -cd.Left;
			}

			for (uint i = 0; i < text.size(); i++)
			{
				char c = text[i];

				const CharacterData& ch = m_Font.GetCharacterData(c);

				if (i == text.size() - 1)
					w += ch.Width + ch.Left;
				else
					w += ch.X_Advance;

				h = ch.Height > h ? ch.Height : h;
			}

			return Maths::Vector2f(w, h);
		}

		Maths::Vector2f FontMetrics::MeasureTextStart(const std::string& text) const
		{
			float left = 0;
			float top = 0;

			if (text.size() > 0)
			{
				const CharacterData& cd = m_Font.GetCharacterData(text[0]);
				left = cd.Left;
				top = cd.Top + cd.Height;
			}

			for (uint i = 0; i < text.size(); i++)
			{
				char c = text[i];

				const CharacterData& ch = m_Font.GetCharacterData(c);

				left = left < ch.Left ? ch.Left : left;
				top = top < (ch.Top + ch.Height) ? (ch.Top + ch.Height) : top;
			}

			return Maths::Vector2f(left, -top);
		}
	}
}