#pragma once

#include <vector>
#include "../Maths/Matrix.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		class TransformationStack
		{
		private:
			std::vector<Maths::Matrix4f> m_Stack;
			Maths::Matrix4f* m_Top;

		public:
			TransformationStack();

			inline void Push(const Maths::Matrix4f& mat)
			{
				m_Stack.push_back(mat * (*m_Top));
				m_Top = &m_Stack.back();
			}

			inline void PushOverride(const Maths::Matrix4f& mat)
			{
				m_Stack.push_back(mat);
				m_Top = &m_Stack.back();
			}

			inline void Pop()
			{
				if (m_Stack.size() > 1)
				{
					m_Stack.pop_back();
					m_Top = &m_Stack.back();
				}
				else
					Debugging::Logger::Log<Debugging::Error>() << "Tried to pop identity matrix from TransformationStack!" << std::endl;
			}

			inline const Maths::Matrix4f& Top() const { return *m_Top; }
		};
	}
}