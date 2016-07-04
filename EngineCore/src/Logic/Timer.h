#pragma once

#ifdef WINDOWS_CLOCK
#include <Windows.h>
#else
#include <chrono>
#endif

namespace Shard
{
#ifdef WINDOWS_CLOCK
	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;

	public:
		Timer()
		{
		}

		void Start()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void Reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float GetElapsedTime()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;

			return (float)(cycles * m_Frequency);
		}
	};
#else
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> m_Start;

	public:
		Timer()
		{
		}

		inline void Start()
		{
			m_Start = HighResolutionClock::now();
		}

		inline float Reset()
		{
			std::chrono::time_point<HighResolutionClock> past = m_Start;
			m_Start = HighResolutionClock::now();
			return std::chrono::duration_cast<milliseconds_type>(m_Start - past).count() / 1000.0f;
		}

		inline float GetElapsedTime()
		{
			return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
		}
	};
#endif
}