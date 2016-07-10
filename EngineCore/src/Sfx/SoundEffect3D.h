#pragma once

#include "SoundEffect.h"
#include "../Maths/Vector3.h"

namespace Shard
{
	namespace Sfx
	{
		class SoundEffect3D : public SoundEffect
		{
		private:
			Maths::Vector3f m_Position;
			Maths::Vector3f m_Velocity;

		public:
			SoundEffect3D(const Resources::Sound& snd);
			SoundEffect3D(const Resources::Sound& snd, const Maths::Vector3f& pos);
			SoundEffect3D(const Resources::Sound& snd, const Maths::Vector3f& pos, const Maths::Vector3f& vel);

			~SoundEffect3D();

			inline void SetPosition(const Maths::Vector3f& pos)
			{
				m_Position = pos;
				alSource3f(m_SourceID, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
			}

			inline void SetVelocity(const Maths::Vector3f& vel)
			{
				m_Velocity = vel;
				alSource3f(m_SourceID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
			}
		};
	}
}