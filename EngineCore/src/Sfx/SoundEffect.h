#pragma once

#include "../Resources/Sound.h"

namespace Shard
{
	namespace Sfx
	{
		class SoundEffect
		{
		protected:
			const Resources::Sound& m_Sound;
			uint m_SourceID;
			float m_Volume;
			float m_Pitch;

		public:
			SoundEffect(const Resources::Sound& sound);
			virtual ~SoundEffect();

			void SetVolume(float vol);
			void SetPitch(float ptch);

			inline float GetVolume() const { return m_Volume; }
			inline float GetPitch() const { return m_Pitch; }

			void Play() const;
			void Loop() const;
			void Pause() const;
			void Resume() const;
			void Stop() const;
		};
	}
}