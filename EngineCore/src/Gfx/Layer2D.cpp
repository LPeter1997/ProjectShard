#include "Layer2D.h"

namespace Shard
{
	namespace Gfx
	{
		Layer2D::Layer2D(Renderer2D* renderer, const GLSLProgram& shader, const Maths::Matrix4f& prMat)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(prMat)
		{
			m_Shader.Enable();

			m_Shader.SetUniformMat4f("pr_matrix", m_ProjectionMatrix);

			static int texIDs[] =
			{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_Shader.SetUniform1iv("textures", texIDs, 32);

			m_Shader.Disable();
		}

		Layer2D::~Layer2D()
		{
			delete m_Renderer;
		}

		void Layer2D::Render()
		{
			m_Shader.Enable();
			m_Renderer->Begin();

			for (Components::Actor* c : m_Renderables)
				c->Render(*m_Renderer);

			m_Renderer->End();
			m_Renderer->Render();
			m_Shader.Disable();
		}

		void Layer2D::Update(float delta)
		{
			for (Components::Actor* c : m_Renderables)
				c->Update(delta);
		}
	}
}