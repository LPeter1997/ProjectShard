#include "BufferLayout.h"

namespace Shard
{
	namespace Gfx
	{
		BufferLayout::BufferLayout()
		{
		}

		void BufferLayout::Push(const std::string& name, uint type, uint size, uint count, bool normalized, bool perInstance)
		{
			m_Elements.push_back({name, type, size, count, 0, normalized, perInstance});
			BufferLayoutElement& element = m_Elements.back();
			if (m_Elements.size() > 1)
			{
				// We need to offset the element if there is a previous entry
				BufferLayoutElement& prev = m_Elements[m_Elements.size() - 2];
				element.Offset = prev.Offset + prev.Size;
			}

			// Size is just where the last element ends
			m_Size = element.Offset + element.Size;
		}
	}
}