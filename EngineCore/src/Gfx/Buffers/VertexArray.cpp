#include "VertexArray.h"

namespace Shard
{
	namespace Gfx
	{
		VertexArray::VertexArray()
			: m_AttribCount(0)
		{
			glGenVertexArrays(1, &m_ArrayID);
		}

		VertexArray::~VertexArray()
		{
			for (VertexBuffer* buf : m_Buffers)
				delete buf;

			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::PushBuffer(VertexBuffer* buffer)
		{
			m_Buffers.push_back(buffer);

			const std::vector<BufferLayoutElement>& layout = buffer->GetLayout().GetElements();
			for (uint i = 0; i < layout.size(); i++, m_AttribCount++)
			{
				glEnableVertexAttribArray(m_AttribCount);
				glVertexAttribPointer(m_AttribCount, layout[i].Count, layout[i].Type, (uint)layout[i].Normalized, buffer->GetLayout().GetStride(), (const GLvoid*)layout[i].Offset);
				if (layout[i].PerInstance)
				{
					glVertexAttribDivisor(m_AttribCount, 1);
				}
			}
		}
	}
}