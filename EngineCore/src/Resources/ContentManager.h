#pragma once

#include <map>
#include <string>
#include "../Types.h"
#include "Resource.h"
#include "../Debugging/Logger.h"
#include "Text.h"
#include "Texture2D.h"

namespace Shard
{
	namespace Resources
	{
		class ContentManager
		{
		private:
			std::map<uint, Resource*> m_Resources;
			uint m_IDcounter;
			std::string m_Root;

		public:
			ContentManager();
			ContentManager(const std::string& root);

			~ContentManager();

			template <typename T = Resource>
			T* GetResource(uint id)
			{
				auto it = m_Resources.find(id);
				if (it != m_Resources.end())
				{
					return it->second;
				}

				return nullptr;
			}

			void Unload(Resource* res);
			void Unload(uint id);
			void UnloadAll();

			// Loading methods
			template <typename T>
			T* Load(const std::string& path)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Generic Load<T>() cannot be used!" << std::endl;
				return nullptr;
			}

			template <>
			Resource* Load(const std::string& path)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Generic Load<Resource>() cannot be used!" << std::endl;
				return nullptr;
			}

			template <>
			Text* Load(const std::string& path)
			{
				Text* text = new Text(m_IDcounter++, m_Root + path);
				text->Load();
				m_Resources.insert(std::make_pair(text->GetResourceID(), text));
				return text;
			}

			template <>
			Texture2D* Load(const std::string& path)
			{
				Texture2D* texture = new Texture2D(m_IDcounter++, m_Root + path);
				texture->Load();
				m_Resources.insert(std::make_pair(texture->GetResourceID(), texture));
				return texture;
			}
		};
	}
}