#pragma once

#include "../Gfx/Renderers/Renderer2D.h"
#include "../Gfx/Shader/GLSLProgram.h"
#include "GUIComponent.h"

namespace Shard
{
	namespace GUI
	{
		class GUILayer
		{
		private:
			Gfx::Renderer2D* m_Renderer;
			std::vector<GUIComponent*> m_Renderables;
			const Gfx::GLSLProgram& m_Shader;
			Maths::Matrix4f m_ProjectionMatrix;

		public:
			GUILayer(Gfx::Renderer2D* renderer, const Gfx::GLSLProgram& shader, const Maths::Matrix4f& prMat);
			virtual ~GUILayer();

			void Render();
			void Update(float delta);

			inline void Add(GUIComponent* renderable)
			{
				m_Renderables.push_back(renderable);
			}
		};
	}
}