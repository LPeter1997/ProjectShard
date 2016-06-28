#include "TransformationStack.h"

namespace Shard
{
	namespace Gfx
	{
		TransformationStack::TransformationStack()
		{
			m_Stack.push_back(Maths::Matrix4f::Identity());
			m_Top = &m_Stack.back();
		}
	}
}