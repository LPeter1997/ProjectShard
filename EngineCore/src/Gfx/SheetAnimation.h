#pragma once

#include "Animation.h"
#include "SpriteSheet.h"
#include "../Types.h"

namespace Shard
{
	namespace Gfx
	{
		class SheetAnimation : public Animation
		{
		private:
			float m_Elapsed;
			float m_FrameTime;
			uint m_CurrentFrame;
			// Sheet data
			const SpriteSheet& m_SpriteSheet;
			uint m_SheetOffset;
			uint m_FrameCount;
			uint m_SheetX;
			uint m_SheetY;

		public:
			SheetAnimation(const SpriteSheet& sheet, float frameTime);
			SheetAnimation(const SpriteSheet& sheet, float frameTime, uint off, uint cnt);

			inline void Update(float delta) override
			{
				m_Elapsed += delta;
				while (m_Elapsed >= m_FrameTime)
				{
					m_CurrentFrame++;
					if (m_CurrentFrame >= m_FrameCount)
						m_CurrentFrame = 0;

					uint sf = m_CurrentFrame + m_SheetOffset;
					m_SheetX = sf % m_SpriteSheet.GetHorizontalSections();
					m_SheetY = sf / m_SpriteSheet.GetHorizontalSections();
					m_Elapsed -= m_FrameTime;
				}
			}

			inline void Draw(const Maths::Vector3f& position, Renderer2D& renderer) override
			{
				renderer.DrawTexture(position, m_SpriteSheet, m_SpriteSheet.GetSectionBounds(m_SheetX, m_SheetY));
			}
		};
	}
}