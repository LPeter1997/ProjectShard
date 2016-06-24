#include <fstream>
#include "Text.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Resources
	{
		bool Text::Load()
		{
			if (m_Loaded)
				return true;

			std::ifstream t(m_Path);
			if (t.good())
			{
				m_Text = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
				t.close();
				Debugging::Logger::Log<Debugging::Info>() << "Text file: '" << m_Path << "' loaded successfully!" << std::endl;
				m_Loaded = true;
				return true;
			}

			Debugging::Logger::Log<Debugging::Error>() << "Could not load text file: '" << m_Path << "'!" << std::endl;
			return false;
		}

		void Text::Unload()
		{
			if (!m_Loaded)
				return;

			Debugging::Logger::Log<Debugging::Info>() << "Text file: '" << m_Path << "' unloaded!" << std::endl;

			m_Text.clear();
			m_Loaded = false;
		}
	}
}