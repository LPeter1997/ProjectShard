#pragma once

#include "../TransformationStack.h"

namespace Shard
{
	namespace Gfx
	{
		class Renderer2D
		{
		protected:
			TransformationStack m_TransformationStack;

		protected:
			Renderer2D()
			{
			}

			virtual ~Renderer2D() {}

		public:
			virtual void Begin() {}
			virtual void End() {}
			virtual void Render() = 0;

			inline TransformationStack& GetTransformationStack() { return m_TransformationStack; }
		};
	}
}