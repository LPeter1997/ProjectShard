#include <FreeImage.h>
#include "Image.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Resources
	{
		Image::Image(uint id, const std::string& path)
			: Resource(id, ResourceType::Texture, path)
		{
		}

		bool Image::Load()
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
				Debugging::Logger::Log<Debugging::Error>() << "Could not recognize image format for: '" << m_Path << "'!" << std::endl;
				return false;
			}

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, file);

			if (!dib)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load image: '" << m_Path << "'!" << std::endl;
				return false;
			}

			m_ImageBuffer = FreeImage_ConvertTo32Bits(dib);

			m_Width = FreeImage_GetWidth(m_ImageBuffer);
			m_Height = FreeImage_GetHeight(m_ImageBuffer);

			Debugging::Logger::Log<Debugging::Info>() << "Image '" << m_Path << "' successfully loaded!" << std::endl;

			m_Loaded = true;
			return true;
		}

		void Image::Unload()
		{
			if (!m_Loaded)
				return;

			FreeImage_Unload(m_ImageBuffer);
			m_Loaded = false;

			Debugging::Logger::Log<Debugging::Info>() << "Image '" << m_Path << "' is unloaded!" << std::endl;
		}
	}
}