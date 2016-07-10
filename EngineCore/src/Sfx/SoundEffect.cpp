#include "SoundEffect.h"

namespace Shard
{
	namespace Sfx
	{
		SoundEffect::SoundEffect(const Resources::Sound& sound)
			: m_Sound(sound), m_Volume(1.0f), m_Pitch(1.0f)
		{
			alGenSources(1, &m_SourceID);
			alSourcei(m_SourceID, AL_BUFFER, m_Sound.GetBufferID());
			alSourcef(m_SourceID, AL_PITCH, 1.0f);
			alSourcef(m_SourceID, AL_GAIN, 1.0f);
			alSourcei(m_SourceID, AL_LOOPING, AL_FALSE);
			alSourcei(m_SourceID, AL_SOURCE_RELATIVE, AL_TRUE);
		}

		SoundEffect::~SoundEffect()
		{
			alDeleteSources(1, &m_SourceID);
		}

		void SoundEffect::Play() const
		{
			alSourcei(m_SourceID, AL_LOOPING, AL_FALSE);
			alSourceRewind(m_SourceID);
			alSourcePlay(m_SourceID);
		}

		void SoundEffect::Loop() const
		{
			alSourcei(m_SourceID, AL_LOOPING, AL_TRUE);
			alSourcePlay(m_SourceID);
		}

		void SoundEffect::Pause() const
		{
			alSourcePause(m_SourceID);
		}

		void SoundEffect::Resume() const
		{
			alSourcePlay(m_SourceID);
		}

		void SoundEffect::Stop() const
		{
			alSourceStop(m_SourceID);
		}

		void SoundEffect::SetVolume(float vol)
		{
			if (vol < 0.0f)
				vol = 0.0f;
			else if (vol > 1.0f)
				vol = 1.0f;

			m_Volume = vol;

			alSourcef(m_SourceID, AL_GAIN, m_Volume);
		}

		void SoundEffect::SetPitch(float pitch)
		{
			if (pitch < 0.0f)
				pitch = 0.0f;

			m_Pitch = pitch;

			alSourcef(m_SourceID, AL_PITCH, m_Pitch);
		}
	}
}