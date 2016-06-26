#pragma once

#include "../../Types.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/Vector3.h"
#include "../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderable2D
		{
		protected:
			Maths::Vector3f m_Position;
			Maths::Vector2f m_Size;
			uint m_Color;

		public:
			Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, uint col);
			Renderable2D(const Maths::Vector2f& pos, const Maths::Vector2f& size, const Maths::Vector4f& col);

			virtual ~Renderable2D() {}

			inline const Maths::Vector3f& GetPosition() const { return m_Position; }
			inline const Maths::Vector2f& GetSize() const { return m_Size; }
			inline uint GetColor() const { return m_Color; }

			virtual void Render() = 0;
		};
	}
}