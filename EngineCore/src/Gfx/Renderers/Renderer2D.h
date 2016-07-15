#pragma once

#include "../TransformationStack.h"
#include "../Texture2D.h"
#include "../FontAtlas.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/AABB.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderer2D
		{
		protected:
			TransformationStack m_TransformationStack;

		protected:
			Renderer2D()
			{
			}

		public:
			virtual ~Renderer2D() {}

		public:
			inline TransformationStack& GetTransformationStack() { return m_TransformationStack; }

			virtual void Begin() {}
			virtual void End() {}
			virtual void Render() = 0;

			virtual void DrawRectangle(const Maths::Vector3f& position, const Maths::Vector2f& size, uint color) {}
			virtual void DrawRectangle(const Maths::Vector3f& position, const Maths::Vector2f& size, float rot, uint color) {}

			virtual void DrawLine(const Maths::Vector2f& pos1, const Maths::Vector2f& pos2, float thickness, uint color) {}

			virtual void DrawTexture(const Maths::Vector3f& position, const Texture2D& texture) {}
			virtual void DrawTexture(const Maths::Vector3f& position, const Texture2D& texture, const Maths::AABBf& UVs) {}
			virtual void DrawTexture(const Maths::Vector3f& position, const Maths::Vector2f& size, const Texture2D& texture) {}
			virtual void DrawTexture(const Maths::Vector3f& position, const Maths::Vector2f& size, const Texture2D& texture, const Maths::AABBf& UVs) {}
			virtual void DrawTexture(const Maths::Vector3f& position, float rot, const Texture2D& texture) {}
			virtual void DrawTexture(const Maths::Vector3f& position, float rot, const Texture2D& texture, const Maths::AABBf& UVs) {}
			virtual void DrawTexture(const Maths::Vector3f& position, const Maths::Vector2f& size, float rot, const Texture2D& texture) {}
			virtual void DrawTexture(const Maths::Vector3f& position, const Maths::Vector2f& size, float rot, const Texture2D& texture, const Maths::AABBf& UVs) {}

			virtual void DrawString(const Maths::Vector3f& position, const std::string& text, const FontAtlas& font, uint color) {}
			virtual void DrawString(const Maths::Vector3f& position, const TextMeasurement& metrics, uint color) {}
		};
	}
}