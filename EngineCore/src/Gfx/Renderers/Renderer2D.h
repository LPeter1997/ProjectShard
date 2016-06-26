#pragma once

#include "../Shader/GLSLProgram.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderer2D
		{
		protected:
			const GLSLProgram& m_Shader;

		protected:
			Renderer2D(const GLSLProgram& shader)
				: m_Shader(shader)
			{
			}

			virtual ~Renderer2D() {}

		public:
			virtual void Begin() {}
			virtual void End() {}
			virtual void Render() = 0;
		};
	}
}