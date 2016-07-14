#include "SpriteSheet.h"

namespace Shard
{
	namespace Gfx
	{
		SpriteSheet::SpriteSheet(const Texture2D& texture, uint xp, uint yp)
			: Texture2D(texture), m_HorizontalSections(xp), m_VerticalSections(yp)
		{
			m_Bounds = new Maths::AABBf[xp * yp];

			float pw = ((float)m_Width / (float)xp) / (float)m_Width;
			float ph = ((float)m_Height / (float)yp) / (float)m_Height;

			for (uint i = 0; i < xp; i++)
			{
				for (uint j = 0; j < yp; j++)
				{
					m_Bounds[i + j * xp] = Maths::AABBf(Maths::Vector2f(i * pw, j * ph), Maths::Vector2f(pw, ph));
				}
			}
		}

		SpriteSheet::~SpriteSheet()
		{
			delete[] m_Bounds;
		}
	}
}