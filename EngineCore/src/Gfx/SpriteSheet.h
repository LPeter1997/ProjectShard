#pragma once

#include "Texture2D.h"
#include "../Maths/AABB.h"

namespace Shard
{
	namespace Gfx
	{
		class SpriteSheet : public Texture2D
		{
		private:
			Maths::AABBf* m_Bounds;
			uint m_HorizontalSections;
			uint m_VerticalSections;

		public:
			SpriteSheet(const Texture2D& texture, uint xp, uint yp);
			~SpriteSheet();

			inline const Maths::AABBf& GetSectionBounds(uint x, uint y)
			{
				return m_Bounds[x + y * m_HorizontalSections];
			}

			inline uint GetHorizontalSections() const { return m_HorizontalSections; }
			inline uint GetVerticalSections() const { return m_VerticalSections; }
		};
	}
}