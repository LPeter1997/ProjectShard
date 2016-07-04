#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Resource.h"
#include "../Gfx/FontAtlas.h"
#include "../Gfx/CharacterSet.h"

namespace Shard
{
	namespace Resources
	{
		class Font : public Resource
		{
		private:
			friend class ContentManager;

		private:
			FT_Face m_Face;

		protected:
			Font(uint id, const std::string& path)
				: Resource(id, ResourceType::Text, path)
			{
			}

			bool Load() override;
			void Unload() override;

		public:
			inline Gfx::FontAtlas* RenderAtlas(float size, const std::string& charset = Gfx::CharacterSet::DEFAULT) const { return new Gfx::FontAtlas(m_Face, size, charset); }
		};
	}
}