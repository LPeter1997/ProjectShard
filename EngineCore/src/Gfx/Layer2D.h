#pragma once

#include <vector>
#include "Renderers\Renderer2D.h"
#include "Shader\GLSLProgram.h"
#include "../Maths/Matrix.h"
#include "../Components/Actor.h"

namespace Shard
{
	namespace Gfx
	{
		class Layer2D
		{
		private:
			Renderer2D* m_Renderer;
			std::vector<Components::Actor*> m_Renderables;
			const GLSLProgram& m_Shader;
			Maths::Matrix4f m_ProjectionMatrix;

		public:
			Layer2D(Renderer2D* renderer, const GLSLProgram& shader, const Maths::Matrix4f& prMat);
			virtual ~Layer2D();

			void Render();
			void Update(float delta);

			inline void Add(Components::Actor* renderable)
			{
				m_Renderables.push_back(renderable);
			}
		};
	}
}