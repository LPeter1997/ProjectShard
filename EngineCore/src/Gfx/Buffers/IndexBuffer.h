#pragma once

#include <GL/glew.h>

namespace Shard
{
	namespace Gfx
	{
		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLsizei count, const GLuint* data);
			~IndexBuffer();

			inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); }
			inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

			inline GLuint GetSize() const { return m_Count; }
			inline GLuint GetBufferID() const { return m_BufferID; }
		};
	}
}