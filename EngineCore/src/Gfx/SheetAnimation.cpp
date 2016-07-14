#include "SheetAnimation.h"

namespace Shard
{
	namespace Gfx
	{
		SheetAnimation::SheetAnimation(const SpriteSheet& sheet, float frameTime)
			: m_SpriteSheet(sheet), m_Elapsed(0), m_FrameTime(frameTime), m_CurrentFrame(0),
			m_SheetOffset(0), m_FrameCount(sheet.GetSectionCount()),
			m_SheetX(0), m_SheetY(0)
		{
		}

		SheetAnimation::SheetAnimation(const SpriteSheet& sheet, float frameTime, uint off, uint cnt)
			: m_SpriteSheet(sheet), m_Elapsed(0), m_FrameTime(frameTime), m_CurrentFrame(0),
			m_SheetOffset(off), m_FrameCount(cnt),
			m_SheetX(off % sheet.GetHorizontalSections()), m_SheetY(off / sheet.GetHorizontalSections())
		{
		}
	}
}