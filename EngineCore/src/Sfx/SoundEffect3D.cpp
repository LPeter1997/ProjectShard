#include "SoundEffect3D.h"

namespace Shard
{
	namespace Sfx
	{
		SoundEffect3D::SoundEffect3D(const Resources::Sound& snd)
			: SoundEffect(snd)
		{
			alSourcei(m_SourceID, AL_SOURCE_RELATIVE, AL_FALSE);
		}

		SoundEffect3D::SoundEffect3D(const Resources::Sound& snd, const Maths::Vector3f& pos)
			: SoundEffect(snd), m_Position(pos)
		{
			alSourcei(m_SourceID, AL_SOURCE_RELATIVE, AL_FALSE);
			alSource3f(m_SourceID, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
		}

		SoundEffect3D::SoundEffect3D(const Resources::Sound& snd, const Maths::Vector3f& pos, const Maths::Vector3f& vel)
			: SoundEffect(snd), m_Position(pos), m_Velocity(vel)
		{
			alSourcei(m_SourceID, AL_SOURCE_RELATIVE, AL_FALSE);
			alSource3f(m_SourceID, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
			alSource3f(m_SourceID, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
		}

		SoundEffect3D::~SoundEffect3D()
		{
		}
	}
}