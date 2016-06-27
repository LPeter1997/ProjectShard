#include <FreeImage.h>
#include "Texture2D.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Resources
	{
		TextureWrap Texture2D::s_WrapMode = TextureWrap::Repeat;
		TextureFilter Texture2D::s_FilterMode = TextureFilter::Linear;

		Texture2D::Texture2D(uint id, const std::string& path)
			: Resource(id, ResourceType::Texture, path)
		{
		}

		bool Texture2D::Load()
		{
			if (m_Loaded)
				return true;

			const char* file = m_Path.c_str();

			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP* dib = nullptr;

			fif = FreeImage_GetFileType(m_Path.c_str(), 0);
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(file);

			if (fif == FIF_UNKNOWN)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not recognize texture format for: '" << m_Path << "'!" << std::endl;
				return false;
			}

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, file);

			if (!dib)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load texture: '" << m_Path << "'!" << std::endl;
				return false;
			}

			FIBITMAP* pImage = FreeImage_ConvertTo32Bits(dib);
			BYTE* pixels = FreeImage_GetBits(pImage);

			m_Width = FreeImage_GetWidth(pImage);
			m_Height = FreeImage_GetHeight(pImage);

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)s_FilterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)s_FilterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)s_WrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)s_WrapMode);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			FreeImage_Unload(pImage);

			Debugging::Logger::Log<Debugging::Info>() << "Texture '" << m_Path << "' successfully loaded!" << std::endl;

			m_Loaded = true;
			return true;
		}

		void Texture2D::Unload()
		{
			if (!m_Loaded)
				return;

			glDeleteTextures(1, &m_TextureID);
			m_Loaded = false;

			Debugging::Logger::Log<Debugging::Info>() << "Texture '" << m_Path << "' is unloaded!" << std::endl;
		}
	}
}