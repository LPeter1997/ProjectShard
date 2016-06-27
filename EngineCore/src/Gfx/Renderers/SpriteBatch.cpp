#include <GL/glew.h>
#include "SpriteBatch.h"

namespace Shard
{
	namespace Gfx
	{
		SpriteBatch::SpriteBatch(uint count)
			: m_SpriteCount(count)
		{
			// Initialize batch
			// Construct layout based on vertex data
			BufferLayout layout;
			layout.Push<Maths::Vector3f>("position");
			layout.Push<byte>("color", 4, true);
			layout.Push<float>("TextureID");
			layout.Push<Maths::Vector2f>("UV");

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
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots.at(i));
			}

			m_VAO->Bind();
			m_IBO->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->Unbind();
			m_VAO->Unbind();

			m_IndexCount = 0;
			m_TextureSlots.clear();
		}

		void SpriteBatch::Draw(const Maths::Vector3f& position, const Maths::Vector2f& size, uint color)
		{
			m_Buffer->TextureID = 0;
			m_Buffer->Position = { position.x, position.y, position.z };
			m_Buffer++->Color = color;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = { position.x, position.y + size.y, position.z };
			m_Buffer++->Color = color;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = { position.x + size.x, position.y + size.y, position.z };
			m_Buffer++->Color = color;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = { position.x + size.x, position.y, position.z };
			m_Buffer++->Color = color;

			m_IndexCount += 6;
		}

		void SpriteBatch::Draw(const Maths::Vector3f& position, const Resources::Texture2D& texture)
		{
			const float ts = PushTexture(texture.GetTextureID());

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 0, 1 };
			m_Buffer->Position = { position.x, position.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 0, 0 };
			m_Buffer->Position = { position.x, position.y + texture.GetHeight(), position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 1, 0 };
			m_Buffer->Position = { position.x + texture.GetWidth(), position.y + texture.GetHeight(), position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 1, 1 };
			m_Buffer->Position = { position.x + texture.GetWidth(), position.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_IndexCount += 6;
		}

		float SpriteBatch::PushTexture(GLuint textureID)
		{
			float ts = 0;
			bool found = false;
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots.at(i) == textureID)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= SPRITEBATCH_TEXTURE_SLOTS)
				{
					End();
					Render();
					Begin();
				}

				m_TextureSlots.push_back(textureID);
				ts = (float)m_TextureSlots.size();
			}

			return ts;
		}
	}
}