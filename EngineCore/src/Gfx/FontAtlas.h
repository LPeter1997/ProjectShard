#pragma once

#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Texture2D.h"
#include "FontMetrics.h"

namespace Shard
{
	namespace Resources
	{
		class Font;
	}

	namespace Gfx
	{
		struct CharacterData
		{
			float X_Advance;
			float Y_Advance;

			float Width;
			float Height;

			float Left;
			float Top;

			float X_UV;
			float Y_UV;

			float X_UV2;
			float Y_UV2;
		};

		class FontAtlas : public Texture2D
		{
		private:
			friend class Resources::Font;

		private:
			FT_Face m_Face;
			std::map<char, CharacterData> m_CharList;
			float m_FontSize;
			FontMetrics m_FontMetrics;

		private:
			FontAtlas(FT_Face face, float size, const std::string& charset);

		public:
			~FontAtlas();

			inline const CharacterData& GetCharacterData(char c) const { return m_CharList.find(c)->second; }
			inline float GetFontSize() const { return m_FontSize; }
			inline const FontMetrics& GetFontMetrics() const { return m_FontMetrics; }
		};
	}
}