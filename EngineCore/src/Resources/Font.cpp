#include "Font.h"
#include "../FreeTypeManager.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Resources
	{
		bool Font::Load()
		{
			if (m_Loaded)
				return true;

			FT_Error error = FT_New_Face(FreeTypeManager::GetLibrary(), m_Path.c_str(), 0, &m_Face);
			if (error == FT_Err_Unknown_File_Format)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Font format not supported for: '" << m_Path << "'!" << std::endl;
				return false;
			}
			else if (error)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load font file: '" << m_Path << "'!" << std::endl;
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "Font '" << m_Path << "' successfully loaded!" << std::endl;

			m_Loaded = true;
			return true;
		}

		void Font::Unload()
		{
			if (!m_Loaded)
				return;

			FT_Done_Face(m_Face);
			m_Loaded = false;

			Debugging::Logger::Log<Debugging::Info>() << "Font '" << m_Path << "' is unloaded!" << std::endl;
		}
	}
}