#include "FontAtlas.h"
#include "../Types.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		FontAtlas::FontAtlas(FT_Face face, float size, const std::string& charset)
			: Texture2D(), m_FontSize(size), m_Face(face)
		{
			// width = height = size * 64 (size is in 1/64)
			// 72 DPI
			//(face, 0, size * 64, 0, 0);
			FT_Set_Pixel_Sizes(face, 0, size);

			uint width = 0;
			uint height = 0;

			for (uint i = 0; i < charset.size(); i++)
			{
				if (FT_Load_Char(face, charset[i], FT_LOAD_RENDER))
				{
					// Continue if a character was not found
					Debugging::Logger::Log<Debugging::Error>() << "Could not load glyph: '" << charset[i] << "' [code: " << (int)charset[i] << "]!" << std::endl;
					continue;
				}

				FT_GlyphSlot g = face->glyph;

				width += g->bitmap.width;
				height = (height < g->bitmap.rows ? g->bitmap.rows : height);
			}

			m_Width = width;
			m_Height = height;

			// Generate openGL texture
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);

			uint x = 0;
			for (uint i = 0; i < charset.size(); i++)
			{
				if (FT_Load_Char(face, charset[i], FT_LOAD_RENDER))
					continue;

				FT_GlyphSlot g = face->glyph;

				GLuint * pixels = new GLuint[g->bitmap.width * g->bitmap.rows];
				for (unsigned int j = 0; j < g->bitmap.width * g->bitmap.rows; j++)
				{
					pixels[j] = g->bitmap.buffer[j] << 24 | 0x00ffffff;
				}

				glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

				delete[] pixels;

				CharacterData c;
				c.X_Advance = (float)(g->advance.x >> 6);
				c.Y_Advance = -(float)(g->advance.y >> 6);
				c.Width = (float)g->bitmap.width;
				c.Height = (float)g->bitmap.rows;
				c.Left = (float)g->bitmap_left;
				c.Top = c.Height - (float)g->bitmap_top;
				c.X_UV = (float)x / (float)width;
				c.Y_UV = 0.0f;
				c.X_UV2 = c.X_UV + c.Width / (float)width;
				c.Y_UV2 = c.Y_UV + c.Height / (float)height;

				m_CharList.insert(std::make_pair(charset[i], c));

				x += g->bitmap.width;
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		FontAtlas::~FontAtlas()
		{
		}
	}
}