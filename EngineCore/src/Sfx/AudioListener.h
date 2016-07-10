#pragma once

#include <OpenAL\al.h>
#include "../Patterns/Static.h"
#include "../Maths/Vector3.h"
#include "../Maths/Orientation.h"

namespace Shard
{
	namespace Sfx
	{
		class AudioListener : public Patterns::Static
		{
		private:
			static Maths::Vector3f m_Position;
			static Maths::Vector3f m_Velocity;
			static Maths::Orientationf m_Orientation;

		public:
			static inline void SetPosition(const Maths::Vector3f& position)
			{
				m_Position = position;
				alListener3f(AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
			}

			static inline void SetVelocity(const Maths::Vector3f& velocity)
			{
				m_Velocity = velocity;
				alListener3f(AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
			}

			static inline void SetOrientation(const Maths::Orientationf& orientation)
			{
				m_Orientation = orientation;
				alListenerfv(AL_ORIENTATION, (const float*)&m_Orientation);
			}

			static inline const Maths::Vector3f& GetPosition() { return m_Position; }
			static inline const Maths::Vector3f& GetVelocity() { return m_Velocity; }
			static inline const Maths::Orientationf& GetOrientation() { return m_Orientation; }
		};
	}
}