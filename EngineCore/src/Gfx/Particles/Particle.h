#pragma once

#include "../../Maths/Vector2.h"
#include "../../Maths/Vector4.h"
#include "../../Types.h"
#include "../Renderers/Renderer2D.h"

namespace Shard
{
	namespace Gfx
	{
		struct Particle
		{
		public:
			Maths::Vector2f Position;
			Maths::Vector2f Velocity;
			float Life;
			float Rotation;
			float Scale;
			Texture2D& Texture;

		public:
			Particle(const Maths::Vector2f& pos, const Maths::Vector2f& vel, float life, float rot, float scl, Texture2D& texture);

			Particle& operator=(Particle const& other)
			{
				Position = other.Position;
				Velocity = other.Velocity;
				Life = other.Life;
				Rotation = other.Rotation;
				Scale = other.Scale;
				Texture = other.Texture;
				return *this;
			}
		};
	}
}