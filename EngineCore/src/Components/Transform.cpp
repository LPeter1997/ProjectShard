#include "Transform.h"

namespace Shard
{
	namespace Components
	{
		Transform::Transform()
			: m_Transform(Maths::Matrix4f::Identity()), Scale(Maths::Vector3f(1, 1, 1))
		{
		}

		Transform::Transform(const Maths::Vector3f& position)
			: m_Transform(Maths::Matrix4f::Translation(position)), Position(position), Scale(Maths::Vector3f(1, 1, 1))
		{
		}

		void Transform::RecalculateTransformationMatrix()
		{
			m_Transform = Maths::Matrix4f::Translation(Position).Rotate(Rotation.x, Maths::Vector3f(1, 0, 0)).Rotate(Rotation.y, Maths::Vector3f(0, 1, 0)).Rotate(Rotation.z, Maths::Vector3f(0, 0, 1)).Scale(Scale);
		}
	}
}