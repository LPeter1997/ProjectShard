#pragma once

#include <GL/glew.h>
#include <FreeImage.h>
#include "Resource.h"

namespace Shard
{
	namespace Gfx
	{
		class Texture2D;
	}

	namespace Resources
	{
		class Image : public Resource
		{
		private:
			friend class ContentManager;
			friend class Gfx::Texture2D;

		protected:
			uint m_Width;
			uint m_Height;
			uint m_Bits;

		private:
			FIBITMAP* m_ImageBuffer;

		protected:
			Image(uint id, const std::string& path);

			bool Load() override;
			void Unload() override;

		public:
			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }
		};
	}
}