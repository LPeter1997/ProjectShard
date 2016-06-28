#include <FreeImage.h>
#include "Texture2D.h"

namespace Shard
{
	namespace Gfx
	{
		TextureWrap Texture2D::s_WrapMode = TextureWrap::Repeat;
		TextureFilter Texture2D::s_FilterMode = TextureFilter::Linear;

		Texture2D::Texture2D(const Resources::Image& image)
			: m_TextureID(0), m_Width(image.m_Width), m_Height(image.m_Height)
		{
			BYTE* pixels = FreeImage_GetBits(image.m_ImageBuffer);
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)s_FilterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)s_FilterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)s_WrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)s_WrapMode);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture2D::Texture2D()
			: m_Width(0), m_Height(0), m_TextureID(0)
		{
		}

		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_TextureID);
		}
	}
}