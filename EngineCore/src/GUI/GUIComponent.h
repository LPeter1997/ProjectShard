#pragma once

#include "../Gfx/Renderers/Renderer2D.h"
#include "../Maths/Vector3.h"
#include "../Maths/Vector2.h"

namespace Shard
{
	namespace GUI
	{
		class GUIComponent
		{
		private:
			friend class GUIContainer;

		protected:
			GUIComponent* m_Parent;
			Maths::Vector3f m_Position;
			Maths::Vector2f m_Size;

		public:
			GUIComponent(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector2f& size);
			GUIComponent(const Maths::Vector2f& pos, const Maths::Vector2f& size);

			virtual ~GUIComponent();

			virtual void Update(float delta) {}
			virtual void Render(Gfx::Renderer2D& renderer) {}
		};
	}
}