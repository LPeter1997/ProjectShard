#include "ContentManager.h"

namespace Shard
{
	namespace Resources
	{
		ContentManager::ContentManager()
			: m_IDcounter(1), m_Root("")
		{
			Debugging::Logger::Log<Debugging::Info>() << "ContentManager created with root: '" << m_Root << "'!" << std::endl;
		}

		ContentManager::ContentManager(const std::string& root)
			: m_IDcounter(0)
		{
			m_Root = root;

			// Fix path (no '/' at beginning but at the end)
			for (unsigned int i = 0; i < m_Root.length(); i++)
				if (m_Root[i] == '\\')
					m_Root[i] = '/';

			if (m_Root.length() == 1)
				if (m_Root[0] == '/')
					m_Root = "";

			if (m_Root.length() > 1)
				if (m_Root[m_Root.length() - 1] != '/')
					m_Root += '/';

			Debugging::Logger::Log<Debugging::Info>() << "ContentManager created with root: '" << m_Root << "'!" << std::endl;
		}

		ContentManager::~ContentManager()
		{
			UnloadAll();
		}

		void ContentManager::Unload(Resource* res)
		{
			res->Unload();
			auto it = m_Resources.find(res->m_ResourceID);
			m_Resources.erase(it);
			delete res;
		}

		void ContentManager::Unload(uint id)
		{
			auto it = m_Resources.find(id);
			if (it != m_Resources.end())
			{
				it->second->Unload();
				delete it->second;
				m_Resources.erase(it);
			}
		}

		void ContentManager::UnloadAll()
		{
			for (auto it = m_Resources.begin(); it != m_Resources.end(); it++)
			{
				it->second->Unload();
				delete it->second;
			}

			m_Resources.clear();

			// No resources, reset counter
			m_IDcounter = 1;
		}
	}
}