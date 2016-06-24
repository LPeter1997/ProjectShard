#pragma once

#include "Resource.h"

namespace Shard
{
	namespace Resources
	{
		class Text : public Resource
		{
		private:
			friend class ContentManager;

		private:
			std::string m_Text;

		protected:
			Text(uint id, const std::string& path)
				: Resource(id, ResourceType::Text, path)
			{
			}

			bool Load() override;
			void Unload() override;

		public:
			inline const std::string& GetText() const { return m_Text; }
		};
	}
}