#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include "../../Types.h"
#include "../../Debugging/Logger.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/Vector3.h"
#include "../../Maths/Vector4.h"

namespace Shard
{
	namespace Gfx
	{
		struct BufferLayoutElement
		{
			std::string Name;
			uint Type;
			uint Size;
			uint Count;
			uint Offset;
			bool Normalized;
		};

		class BufferLayout
		{
		private:
			uint m_Size;
			std::vector<BufferLayoutElement> m_Elements;

		public:
			BufferLayout();

			inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }
			inline uint GetStride() const { return m_Size; }

			// Pushing layout elements
			template <typename T>
			inline void Push(const std::string& name, uint count = 1, bool normalized = false)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Wrong type specifier for Push<T>()!" << std::endl;
			}

			template<>
			inline void Push<float>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_FLOAT, sizeof(float) * count, count, normalized);
			}

			template<>
			inline void Push<uint>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_UNSIGNED_INT, sizeof(uint) * count, count, normalized);
			}

			template<>
			inline void Push<byte>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_UNSIGNED_BYTE, sizeof(byte) * count, count, normalized);
			}

			template<>
			inline void Push<Maths::Vector2f>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_FLOAT, sizeof(Maths::Vector2f) * count, 2 * count, normalized);
			}

			template<>
			inline void Push<Maths::Vector3f>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_FLOAT, sizeof(Maths::Vector3f) * count, 3 * count, normalized);
			}

			template<>
			inline void Push<Maths::Vector4f>(const std::string& name, uint count, bool normalized)
			{
				Push(name, GL_FLOAT, sizeof(Maths::Vector4f) * count, 4 * count, normalized);
			}

		private:
			// The generic Push()
			void Push(const std::string& name, uint type, uint size, uint count, bool normalized);
		};
	}
}