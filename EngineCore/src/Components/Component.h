#pragma once

#include "../Gfx/Renderers/Renderer2D.h"

namespace Shard
{
	namespace Components
	{
		class Actor;

		class Component
		{
		protected:
			Actor& m_Actor;

		public:
			Component(Actor& actor)
				: m_Actor(actor)
			{
			}

			virtual void Update(float delta) {}
			virtual void Render(Gfx::Renderer2D& render) {}
		};
	}
}