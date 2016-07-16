#pragma once

#include <GL/glew.h>
#include "../../Types.h"
#include "BufferLayout.h"

namespace Shard
{
	namespace Gfx
	{
		class VertexBuffer
		{
		private:
			GLuint m_BufferID;
			uint m_Target, m_Usage;
			uint m_Size;
			BufferLayout m_Layout;

		public:
			VertexBuffer(uint target, uint usage, BufferLayout layout);
			~VertexBuffer();

			inline GLuint GetBufferID() const { return m_BufferID; }
			inline uint GetTarget() const { return m_Target; }
			inline uint GetUsage() const { return m_Usage; }
			inline uint GetSize() const { return m_Size; }
			inline const BufferLayout& GetLayout() const { return m_Layout; }

			void Resize(uint size);
			void SetData(uint size, const void* data);
			void SetSubData(uint offset, uint size, const void* data);

			template <typename T>
			inline T* GetPointer(uint flags = GL_WRITE_ONLY) const
			{
				return (T*)glMapBuffer(m_Target, flags);
			}

			inline void ReleasePointer() const
			{
				glUnmapBuffer(m_Target);
			}

			inline void Bind() const
			{
				glBindBuffer(m_Target, m_BufferID);
			}

			inline void Unbind() const
			{
				glBindBuffer(m_Target, 0);
			}
		};
	}
}