#pragma once

#include <GL/glew.h>
#include <vector>
#include "VertexBuffer.h"


namespace Shard
{
	namespace Gfx
	{
		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<VertexBuffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			inline VertexBuffer* GetBuffer(unsigned int idx = 0) { return m_Buffers[idx]; }

			void PushBuffer(VertexBuffer* buffer);

			inline void Bind() const { glBindVertexArray(m_ArrayID); }
			inline void Unbind() const { glBindVertexArray(0); }

			inline GLuint GetArrayID() const { return m_ArrayID; }
		};
	}
}