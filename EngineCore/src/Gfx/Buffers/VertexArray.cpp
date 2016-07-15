#include "VertexArray.h"

namespace Shard
{
	namespace Gfx
	{
		VertexArray::VertexArray()
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
			for (uint i = 0; i < layout.size(); i++)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, layout[i].Count, layout[i].Type, (uint)layout[i].Normalized, buffer->GetLayout().GetStride(), (const GLvoid*)layout[i].Offset);
				if (layout[i].PerInstance)
				{
					glVertexAttribDivisor(i, 1);
				}
			}
		}
	}
}