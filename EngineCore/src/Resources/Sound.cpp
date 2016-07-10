#include "Sound.h"
#include "../Debugging/Logger.h"

namespace Shard
{
	namespace Resources
	{
		Sound::Sound(uint id, const std::string& path)
			: Resource(id, ResourceType::Sound, path), m_Format(0), m_Frequency(0)
		{
		}

		bool Sound::Load()
		{
			if (m_Loaded)
				return true;

			FILE* file = nullptr;
			file = std::fopen(m_Path.c_str(), "rb");
			if (!file)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load sound: '" << m_Path << "'!" << std::endl;
				return false;
			}

			char type[4];
			uint size, chunkSize;
			short formatType, channels;
			uint sampleRate, avgBytesPerSec;
			short bytesPerSample, bitsPerSample;
			uint dataSize;

			std::fread(type, sizeof(char), 4, file);
			if (std::strncmp(type, "RIFF", 4))
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load sound: '" << m_Path << "' (Not 'RIFF')!" << std::endl;
				return false;
			}

			std::fread(&size, sizeof(uint), 1, file);

			std::fread(type, sizeof(char), 4, file);
			if (std::strncmp(type, "WAVE", 4))
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load sound: '" << m_Path << "' (Not 'WAVE')!" << std::endl;
				return false;
			}

			std::fread(type, sizeof(char), 4, file);
			if (std::strncmp(type, "fmt ", 4))
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not load sound: '" << m_Path << "' (Not 'fmt ')!" << std::endl;
				return false;
			}

			// Now it's an acceptable WAVE file, read attributes
			std::fread(&chunkSize, sizeof(uint), 1, file);
			std::fread(&formatType, sizeof(short), 1, file);
			std::fread(&channels, sizeof(short), 1, file);
			std::fread(&sampleRate, sizeof(uint), 1, file);
			std::fread(&avgBytesPerSec, sizeof(uint), 1, file);
			std::fread(&bytesPerSample, sizeof(short), 1, file);
			std::fread(&bitsPerSample, sizeof(short), 1, file);

			// Data part
			std::fread(&type, sizeof(char), 4, file);
			if (std::strncmp(type, "data", 4))
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not find sound data: '" << m_Path << "'!" << std::endl;
				return false;
			}

			std::fread(&dataSize, sizeof(uint), 1, file);
			byte* buffer = new byte[dataSize];
			std::fread(buffer, sizeof(byte), dataSize, file);

			m_Frequency = sampleRate;

			// OpenAL
			alGenBuffers(1, &m_BufferID);
			ALenum error = alGetError();
			if (error != AL_NO_ERROR)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Could not create audio-buffer!" << std::endl;
				return false;
			}

			if (bitsPerSample == 8)
			{
				if (channels == 1)
				{
					m_Format = AL_FORMAT_MONO8;
				}
				else if (channels == 2)
				{
					m_Format = AL_FORMAT_STEREO8;
				}
			}
			else if (bitsPerSample == 16)
			{
				if (channels == 1)
				{
					m_Format = AL_FORMAT_MONO16;
				}
				else if (channels == 2)
				{
					m_Format = AL_FORMAT_STEREO16;
				}
			}

			if (!m_Format)
			{
				Debugging::Logger::Log<Debugging::Error>() << "Unknown audio format for: '" << m_Path << "'!" << std::endl;
				return false;
			}

			alBufferData(m_BufferID, m_Format, buffer, dataSize, m_Frequency);
			delete[] buffer;

			/////////

			Debugging::Logger::Log<Debugging::Info>() << "Sound '" << m_Path << "' successfully loaded!" << std::endl;

			m_Loaded = true;
			return true;
		}

		void Sound::Unload()
		{
			if (!m_Loaded)
				return;

			alDeleteBuffers(1, &m_BufferID);

			m_Loaded = false;
			Debugging::Logger::Log<Debugging::Info>() << "Sound '" << m_Path << "' is unloaded!" << std::endl;
		}
	}
}