#pragma once

#include "../Maths/Vector3.h"
#include "../Maths/Matrix.h"

namespace Shard
{
	namespace Components
	{
		class Transform
		{
		private:
			Maths::Matrix4f m_Transform;

		private:
			Maths::Vector3f m_Position;
			Maths::Vector3f m_Scale;
			Maths::Vector3f m_Rotation;

		public:
			Transform();
			Transform(const Maths::Vector3f& position);

			inline const Maths::Matrix4f& GetTransformationMatrix() { return m_Transform; }

			inline void SetPosition(const Maths::Vector3f& pos) { m_Position = pos; RecalculateTransformationMatrix(); }
			inline void SetScale(const Maths::Vector3f& scl) { m_Scale = scl; RecalculateTransformationMatrix(); }
			inline void SetRotation(const Maths::Vector3f& rot) { m_Rotation = rot; RecalculateTransformationMatrix(); }

			inline void AddPosition(const Maths::Vector3f& pos) { m_Position += pos; m_Transform.Translate(pos); }
			inline void AddScale(const Maths::Vector3f& scl) { m_Scale += scl; m_Transform.Scale(scl); }
			inline void AddRotation(const Maths::Vector3f& rot) { m_Rotation += rot; m_Transform.Rotate(m_Rotation.x, Maths::Vector3f(1, 0, 0)).Rotate(m_Rotation.y, Maths::Vector3f(0, 1, 0)).Rotate(m_Rotation.z, Maths::Vector3f(0, 0, 1)); }

			inline const Maths::Vector3f& GetPosition() const { return m_Position; }
			inline const Maths::Vector3f& GetScale() const { return m_Scale; }
			inline const Maths::Vector3f& GetRotation() const { return m_Rotation; }

		private:
			void RecalculateTransformationMatrix();
		};
	}
}