#include <GL/glew.h>
#include "SpriteBatch.h"

namespace Shard
{
	namespace Gfx
	{
		SpriteBatch::SpriteBatch(const GLSLProgram& shader, uint count)
			: Renderer2D(shader), m_SpriteCount(count)
		{
			// Initialize batch
			// Construct layout based on vertex data
			BufferLayout layout;
			layout.Push<Maths::Vector3f>("position");
			layout.Push<byte>("color", 4, true);
			layout.Push<Maths::Vector2f>("UV");
			layout.Push<float>("TextureID");

			m_VBO = new VertexBuffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW, layout);
			m_VBO->Bind();
			m_VBO->Resize(sizeof(VertexData2D) * 4 * m_SpriteCount);

			m_VAO = new VertexArray();
			m_VAO->Bind();
			m_VAO->PushBuffer(m_VBO);

			// 6 indicies per sprite
			const uint indicies_count = m_SpriteCount * 6;
			GLuint* indicies = new uint[indicies_count];

			uint offset = 0;
			for (uint i = 0; i < indicies_count; i += 6)
			{
				indicies[  i  ] = offset + 0;
				indicies[i + 1] = offset + 1;
				indicies[i + 2] = offset + 2;

				indicies[i + 3] = offset + 2;
				indicies[i + 4] = offset + 3;
				indicies[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indicies_count, indicies);
			m_VAO->Unbind();
			m_VBO->Unbind();
		}

		SpriteBatch::~SpriteBatch()
		{
			delete m_VAO;	// Also deletes our VBO
			delete m_IBO;
		}

		void SpriteBatch::Begin()
		{
			m_VBO->Bind();
			m_Buffer = m_VBO->GetPointer<VertexData2D>();
		}

		void SpriteBatch::End()
		{
			m_VBO->ReleasePointer();
			m_VBO->Unbind();
		}

		void SpriteBatch::Render()
		{
			m_VAO->Bind();
			m_IBO->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->Unbind();
			m_VAO->Unbind();

			m_IndexCount = 0;
		}

		void SpriteBatch::Draw(const Maths::Vector3f& pos, const Maths::Vector2f& size, uint color)
		{
			Maths::Vector3f position = pos;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = position;
			m_Buffer++->Color = color;
			//++m_Buffer;

			position.y += size.y;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = position;
			m_Buffer++->Color = color;
			//++m_Buffer;

			position.x += size.x;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = position;
			m_Buffer++->Color = color;
			//++m_Buffer;

			position.y -= size.y;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = position;
			m_Buffer++->Color = color;
			//++m_Buffer;

			m_IndexCount += 6;
		}
	}
}