#include "Transform.h"

namespace Shard
{
	namespace Components
	{
		Transform::Transform()
			: m_Transform(Maths::Matrix4f::Identity()), m_Scale(Maths::Vector3f(1, 1, 1))
		{
		}

		Transform::Transform(const Maths::Vector3f& position)
			: m_Transform(Maths::Matrix4f::Translation(position)), m_Position(position), m_Scale(Maths::Vector3f(1, 1, 1))
		{
		}

		void Transform::RecalculateTransformationMatrix()
		{
			m_Transform = Maths::Matrix4f::Translation(m_Position).Rotate(m_Rotation.x, Maths::Vector3f(1, 0, 0)).Rotate(m_Rotation.y, Maths::Vector3f(0, 1, 0)).Rotate(m_Rotation.z, Maths::Vector3f(0, 0, 1)).Scale(m_Scale);
		}
	}
}