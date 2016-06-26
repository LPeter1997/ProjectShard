#pragma once

#include "../../Types.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderable2D
		{
		protected:
			Maths::Vector2f m_Position;
			Maths::Vector2f m_Size;
			uint m_Color;

		public:
			Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, uint col);
			Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, const Maths::Vector4f& col);

			virtual ~Renderable2D() {}

			virtual void Render() = 0;
		};
	}
}