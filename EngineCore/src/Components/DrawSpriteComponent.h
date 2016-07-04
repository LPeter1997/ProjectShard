#pragma once

#include "Component.h"
#include "../Gfx/Texture2D.h"
#include "Transform.h"

namespace Shard
{
	namespace Components
	{
		class DrawSpriteComponent : public Component
		{
		protected:
			Transform& m_Position;

		public:
			Gfx::Texture2D* Texture;

		public:
			DrawSpriteComponent(Actor& a)
				: Component(a), m_Position(m_Actor.GetTransform()), Texture(nullptr)
			{
			}

			inline void Render(Gfx::Renderer2D& renderer) override
			{
				renderer.Draw(m_Position.Position, *Texture);
			}
		};
	}
}