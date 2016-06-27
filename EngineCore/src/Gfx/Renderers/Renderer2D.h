#pragma once

#include "../Shader/GLSLProgram.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderer2D
		{
		protected:

		protected:
			Renderer2D()
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