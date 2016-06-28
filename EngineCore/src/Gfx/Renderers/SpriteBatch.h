#pragma once

#include "Renderer2D.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"
#include "../VertexData2D.h"
#include "../Texture2D.h"
#include "../FontAtlas.h"

#define SPRITEBATCH_TEXTURE_SLOTS 32

namespace Shard
{
	namespace Gfx
	{
		class SpriteBatch : public Renderer2D
		{
		private:
			const uint m_SpriteCount;
			VertexArray* m_VAO;
			VertexBuffer* m_VBO;
			IndexBuffer* m_IBO;
			uint m_IndexCount;
			VertexData2D* m_Buffer;
			std::vector<GLuint> m_TextureSlots;

		public:
			SpriteBatch(uint count);

			~SpriteBatch();

			void Begin() override;
			void End() override;
			void Render() override;

			void Draw(const Maths::Vector3f& position, const Maths::Vector2f& size, uint color);
			void Draw(const Maths::Vector3f& position, const Texture2D& texture);

			void DrawString(const Maths::Vector3f& position, const std::string& text, FontAtlas& font, uint color);

		private:
			float PushTexture(GLuint textureID);
		};
	}
}