#pragma once

#include "Renderer2D.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"
#include "../VertexData2D.h"

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

		public:
			//SpriteBatch(const GLSLProgram& shader);
			SpriteBatch(const GLSLProgram& shader, uint count);

			~SpriteBatch();

			void Begin() override;
			void End() override;
			void Render() override;

			void Draw(const Maths::Vector3f& pos, const Maths::Vector2f& size, uint color);
		};
	}
}