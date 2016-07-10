#pragma once

#include <OpenAL\al.h>
#include "Resource.h"

namespace Shard
{
	namespace Resources
	{
		class Sound : public Resource
		{
		private:
			friend class ContentManager;

		private:
			uint m_BufferID;
			ALenum m_Format;
			ALuint m_Frequency;

		protected:
			Sound(uint id, const std::string& path);

			bool Load() override;
			void Unload() override;

		public:
			inline uint GetBufferID() const { return m_BufferID; }
		};
	}
}