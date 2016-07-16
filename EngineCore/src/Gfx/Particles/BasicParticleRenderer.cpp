#include "BasicParticleRenderer.h"

namespace Shard
{
	namespace Gfx
	{
		BasicParticleRenderer::BasicParticleRenderer()
			: m_ParticleSystem(nullptr), m_PositionBuffer(nullptr), m_ColorBuffer(nullptr)
		{
		}

		void BasicParticleRenderer::Generate(ParticleSystem* psys)
		{
			m_ParticleSystem = psys;

			const uint count = psys->ParticleCount();

			// Construct first layout
			BufferLayout layout1;
			layout1.Push<Maths::Vector4f>("position");

			m_PositionBuffer = new VertexBuffer(GL_ARRAY_BUFFER, GL_STREAM_DRAW, layout1);
			m_PositionBuffer->Bind();
			m_PositionBuffer->Resize(sizeof(Maths::Vector4f) * count);

			// Construct second layout
			BufferLayout layout2;
			layout2.Push<Maths::Vector4f>("color");

			m_ColorBuffer = new VertexBuffer(GL_ARRAY_BUFFER, GL_STREAM_DRAW, layout2);
			m_ColorBuffer->Bind();
			m_ColorBuffer->Resize(sizeof(Maths::Vector4f) * count);

			m_VAO = new VertexArray();
			m_VAO->Bind();

			m_PositionBuffer->Bind();
			m_VAO->PushBuffer(m_PositionBuffer);
			m_PositionBuffer->Unbind();
			m_ColorBuffer->Bind();
			m_VAO->PushBuffer(m_ColorBuffer);
			m_ColorBuffer->Unbind();
			m_VAO->Unbind();
		}

		void BasicParticleRenderer::Destroy()
		{
			if (m_VAO) delete m_VAO;	// Also deletes VBOs
		}

		void BasicParticleRenderer::Update()
		{
			const uint count = m_ParticleSystem->AliveParticleCount();
			if (count)
			{
				m_PositionBuffer->Bind();
				float* ptr = (float*)(m_ParticleSystem->ParticleData()->Positions);
				m_PositionBuffer->SetSubData(0, sizeof(Maths::Vector4f) * count, ptr);
				m_PositionBuffer->Unbind();

				m_ColorBuffer->Bind();
				ptr = (float*)(m_ParticleSystem->ParticleData()->Colors);
				m_ColorBuffer->SetSubData(0, sizeof(Maths::Vector4f) * count, ptr);
				m_ColorBuffer->Unbind();
			}
		}

		void BasicParticleRenderer::Render()
		{

			uint count = m_ParticleSystem->AliveParticleCount();
			if (count)
			{
				
				m_VAO->Bind();
				glDrawArrays(GL_POINTS, 0, count);
				m_VAO->Unbind();
				
			}

		}
	}
}