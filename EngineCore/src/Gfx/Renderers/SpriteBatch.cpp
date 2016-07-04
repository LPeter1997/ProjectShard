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

		void SpriteBatch::DrawRectangle(const Maths::Vector3f& position, const Maths::Vector2f& size, uint color)
		{
			Maths::Vector3f pos = position;
			const Maths::Matrix4f& trans_top = m_TransformationStack.Top();

			m_Buffer->TextureID = 0;
			m_Buffer->Position = trans_top * pos;
			m_Buffer++->Color = color;

			pos.y += size.y;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = trans_top * pos;
			m_Buffer++->Color = color;

			pos.x += size.x;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = trans_top * pos;
			m_Buffer++->Color = color;

			pos.y -= size.y;

			m_Buffer->TextureID = 0;
			m_Buffer->Position = trans_top * pos;
			m_Buffer++->Color = color;

			m_IndexCount += 6;
		}

		void SpriteBatch::DrawLine(const Maths::Vector2f& pos1, const Maths::Vector2f& pos2, float thickness, uint color)
		{
			const Maths::Matrix4f& trans = m_TransformationStack.Top();
			Maths::Vector3f& normal = thickness * Maths::Vector3f(pos2.y - pos1.y, -(pos2.x - pos1.x), 0).Normalize();

			m_Buffer->Position = trans * Maths::Vector3f(pos1.x + normal.x, pos1.y + normal.y, 0.0f);
			m_Buffer->TextureID = 0;
			m_Buffer->Color = color;
			m_Buffer++;

			m_Buffer->Position = trans * Maths::Vector3f(pos2.x + normal.x, pos2.y + normal.y, 0.0f);
			m_Buffer->TextureID = 0;
			m_Buffer->Color = color;
			m_Buffer++;

			m_Buffer->Position = trans * Maths::Vector3f(pos2.x - normal.x, pos2.y - normal.y, 0.0f);
			m_Buffer->TextureID = 0;
			m_Buffer->Color = color;
			m_Buffer++;

			m_Buffer->Position = trans * Maths::Vector3f(pos1.x - normal.x, pos1.y - normal.y, 0.0f);
			m_Buffer->TextureID = 0;
			m_Buffer->Color = color;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void SpriteBatch::DrawTexture(const Maths::Vector3f& position, const Texture2D& texture)
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

		void SpriteBatch::DrawTexture(const Maths::Vector3f& position, const Maths::Vector3f& size, const Texture2D& texture)
		{
			const float ts = PushTexture(texture.GetTextureID());

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 0, 1 };
			m_Buffer->Position = { position.x, position.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 0, 0 };
			m_Buffer->Position = { position.x, position.y + size.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 1, 0 };
			m_Buffer->Position = { position.x + size.x, position.y + size.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_Buffer->TextureID = ts;
			m_Buffer->UV = { 1, 1 };
			m_Buffer->Position = { position.x + size.x, position.y, position.z };
			m_Buffer++->Color = 0xffffffff;

			m_IndexCount += 6;
		}

		void SpriteBatch::DrawString(const Maths::Vector3f& position, const std::string& text, const FontAtlas& font, uint color)
		{
			Maths::Vector3f pos = position;

			Maths::Vector2f st = font.GetFontMetrics().MeasureTextStart(text);

			pos.x -= st.x;
			pos.y -= st.y;
			
			const Maths::Matrix4f& trans = m_TransformationStack.Top();

			float ts = PushTexture(font.GetTextureID());

			for (uint i = 0; i < text.size(); i++)
			{
				char ch = text[i];

				const CharacterData& charData = font.GetCharacterData(ch);
				
				float x2 = pos.x + charData.Left;
				float y2 = pos.y + charData.Top;

				m_Buffer->Position = trans * Maths::Vector3f(x2, y2, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV, charData.Y_UV2 };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2, y2 - charData.Height, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV, charData.Y_UV };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2 + charData.Width, y2 - charData.Height, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV2, charData.Y_UV };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2 + charData.Width, y2, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV2, charData.Y_UV2 };
				m_Buffer->Color = color;
				m_Buffer++;

				pos.x += charData.X_Advance;
				pos.y += charData.Y_Advance;

				m_IndexCount += 6;
			}
		}

		void SpriteBatch::DrawString(const Maths::Vector3f& position, const TextMeasurement& metrics, uint color)
		{
			const FontAtlas& font = metrics.Font;
			const std::string& text = metrics.Text;

			Maths::Vector3f pos = position;
			Maths::Vector2f st = metrics.Start;

			pos.x -= st.x;
			pos.y -= st.y;

			const Maths::Matrix4f& trans = m_TransformationStack.Top();

			float ts = PushTexture(font.GetTextureID());

			for (uint i = 0; i < text.size(); i++)
			{
				char ch = text[i];

				const CharacterData& charData = font.GetCharacterData(ch);

				float x2 = pos.x + charData.Left;
				float y2 = pos.y + charData.Top;

				m_Buffer->Position = trans * Maths::Vector3f(x2, y2, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV, charData.Y_UV2 };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2, y2 - charData.Height, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV, charData.Y_UV };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2 + charData.Width, y2 - charData.Height, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV2, charData.Y_UV };
				m_Buffer->Color = color;
				m_Buffer++;

				m_Buffer->Position = trans * Maths::Vector3f(x2 + charData.Width, y2, 0);
				m_Buffer->TextureID = ts;
				m_Buffer->UV = { charData.X_UV2, charData.Y_UV2 };
				m_Buffer->Color = color;
				m_Buffer++;

				pos.x += charData.X_Advance;
				pos.y += charData.Y_Advance;

				m_IndexCount += 6;
			}
		}

		float SpriteBatch::PushTexture(GLuint textureID)
		{
			// Found
			for (uint i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots.at(i) == textureID)
					return (float)(i + 1);
			}

			// Not found
			if (m_TextureSlots.size() >= SPRITEBATCH_TEXTURE_SLOTS)
			{
				End();
				Render();
				Begin();
			}

			m_TextureSlots.push_back(textureID);
			return (float)m_TextureSlots.size();
		}
	}
}