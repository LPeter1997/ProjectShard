#pragma once

#include <string>
#include "../Types.h"

namespace Shard
{
	namespace Resources
	{
		enum class ResourceType
		{
			Text
		};

		class Resource
		{
		private:
			friend class ContentManager;

		private:
			uint m_ResourceID;
			ResourceType m_ResourceType;

		protected:
			std::string m_Path;
			bool m_Loaded;

		protected:
			Resource(uint id, ResourceType type, const std::string& path)
				: m_ResourceID(id), m_ResourceType(type), m_Loaded(false)
			{
				m_Path = path;

				// Fix path (no '/' at beginning)
				for (uint i = 0; i < m_Path.length(); i++)
					if (m_Path[i] == '\\')
						m_Path[i] = '/';

				if (m_Path.length() > 0)
				{
					if (m_Path[0] == '/')
						m_Path = m_Path.substr(1, m_Path.length() - 1);
				}
			}

		public:
			inline uint GetResourceID() const { return m_ResourceID; }
			inline ResourceType GetResourceType() const { return m_ResourceType; }
			inline const std::string& GetFilePath() const { return m_Path; }
			inline bool IsLoaded() const { return m_Loaded; }

		protected:
			virtual bool Load() = 0;
			virtual void Unload() = 0;
		};
	}
}