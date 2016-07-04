#pragma once

#include <string>
#include "../Maths/Vector2.h"

namespace Shard
{
	namespace Gfx
	{
		class FontAtlas;

		struct TextMeasurement
		{
			const FontAtlas& Font;
			std::string Text;
			Maths::Vector2f Start;
			Maths::Vector2f Size;

			TextMeasurement(const FontAtlas& font, const std::string& text, const Maths::Vector2f& start, const Maths::Vector2f& size)
				: Font(font), Text(text), Start(start), Size(size)
			{
			}

			TextMeasurement& operator=(const TextMeasurement& other)
			{
				Text = other.Text;
				Start = other.Start;
				Size = other.Size;
				return *this;
			}
		};

		class FontMetrics
		{
		private:
			const FontAtlas& m_Font;

		public:
			FontMetrics(const FontAtlas& font);
			
			TextMeasurement MeasureText(const std::string& text) const;
			Maths::Vector2f MeasureTextSize(const std::string& text) const;
			Maths::Vector2f MeasureTextStart(const std::string& text) const;
		};
	}
}