#include "FontAtlas.h"
#include "../Types.h"
#include "../Debugging/Logger.h"
#include "Packer.h"

namespace Shard
{
	namespace Gfx
	{
		FontAtlas::FontAtlas(FT_Face face, float size, const std::string& charset)
			: Texture2D(), m_FontSize(size), m_Face(face)
		{
			Packer<char> packer;

			// width = height = size * 64 (size is in 1/64)
			// 72 DPI
			//(face, 0, size * 64, 0, 0);
			FT_Set_Pixel_Sizes(face, 0, size);

			for (uint i = 0; i < charset.size(); i++)
			{
				if (FT_Load_Char(face, charset[i], FT_LOAD_RENDER))
				{
					// Continue if a character was not found
					Debugging::Logger::Log<Debugging::Error>() << "Could not load glyph: '" << charset[i] << "' [code: " << (int)charset[i] << "]!" << std::endl;
					continue;
				}

				FT_GlyphSlot g = face->glyph;

				packer.Push(charset[i], g->bitmap.width, g->bitmap.rows);
			}

			packer.Pack();

			m_Width = packer.GetPackWidth();
			m_Height = packer.GetPackHeight();

			// Generate openGL texture
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);

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

				const PackerResult& res = packer.Get(charset[i]);

				glTexSubImage2D(GL_TEXTURE_2D, 0, res.X, res.Y, g->bitmap.width, g->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

				delete[] pixels;

				CharacterData c;
				c.X_Advance = (float)(g->advance.x >> 6);
				c.Y_Advance = -(float)(g->advance.y >> 6);
				c.Width = (float)g->bitmap.width;
				c.Height = (float)g->bitmap.rows;
				c.Left = (float)g->bitmap_left;
				c.Top = c.Height - (float)g->bitmap_top;
				c.X_UV = (float)res.X / (float)m_Width;
				c.Y_UV = (float)res.Y / (float)m_Height;
				c.X_UV2 = c.X_UV + c.Width / (float)m_Width;
				c.Y_UV2 = c.Y_UV + c.Height / (float)m_Height;

				m_CharList.insert(std::make_pair(charset[i], c));
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			m_FontMetrics = new FontMetrics(*this);
		}
		
		FontAtlas::~FontAtlas()
		{
			delete m_FontMetrics;
		}
	}
}