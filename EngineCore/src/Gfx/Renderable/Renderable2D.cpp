#include "Renderable2D.h"
#include "../ColorUtils.h"

namespace Shard
{
	namespace Gfx
	{
		Renderable2D::Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, uint col)
			: m_Position(Maths::Vector3f(pos.x, pos.y, 0.0f)), m_Size(size), m_Color(col)
		{
		}

		Renderable2D::Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, const Maths::Vector4f& col)
			: Renderable2D(pos, size, ColorUtils::RGBATo32Int(col))
		{
		}
	}
}