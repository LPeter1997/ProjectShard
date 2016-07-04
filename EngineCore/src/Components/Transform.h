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

		public:
			Maths::Vector3f Position;
			Maths::Vector3f Scale;
			Maths::Vector3f Rotation;

		public:
			Transform();
			Transform(const Maths::Vector3f& position);

			inline const Maths::Matrix4f& GetTransformationMatrix() { RecalculateTransformationMatrix(); return m_Transform; }

		private:
			void RecalculateTransformationMatrix();
		};
	}
}