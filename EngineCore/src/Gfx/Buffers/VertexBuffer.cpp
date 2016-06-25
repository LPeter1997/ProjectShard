#include "VertexBuffer.h"

namespace Shard
{
	namespace Gfx
	{
		VertexBuffer::VertexBuffer(uint target, uint usage, BufferLayout layout)
			: m_Target(target), m_Usage(usage), m_Layout(layout)
		{
			glGenBuffers(1, &m_BufferID);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void VertexBuffer::Resize(uint size)
		{
			m_Size = size;
			glBufferData(m_Target, size, nullptr, m_Usage);
		}

		void VertexBuffer::SetData(uint size, const void* data)
		{
			m_Size = size;
			glBufferData(m_Target, size, data, m_Usage);
		}
	}
}