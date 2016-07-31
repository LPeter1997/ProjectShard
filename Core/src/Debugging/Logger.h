#pragma once

#include <ostream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "LogLevel.h"

namespace Shard
{
	namespace Debugging
	{
		class Logger
		{
		private:
			static std::ostream& s_Ostream;

		private:
			Logger() = delete;

		public:
			template <typename Level>
			static inline std::ostream& Log()
			{
				auto t = std::time(nullptr);
				auto tm = *std::localtime(&t);
				return s_Ostream << '[' << std::put_time(&tm, "%H:%M:%S") << "] " << Level::GetDescription() << ' ' << (unsigned int)Level::GetLevel() << ": ";
			}

			// Short names
			static inline std::ostream& d()
			{
				return Log<Debug>();
			}

			static inline std::ostream& i()
			{
				return Log<Info>();
			}

			static inline std::ostream& w()
			{
				return Log<Warning>();
			}

			static inline std::ostream& e()
			{
				return Log<Error>();
			}

			static inline std::ostream& f()
			{
				return Log<Fatal>();
			}

			// Long names
			static inline std::ostream& debug()
			{
				return Log<Debug>();
			}

			static inline std::ostream& info()
			{
				return Log<Info>();
			}

			static inline std::ostream& warning()
			{
				return Log<Warning>();
			}

			static inline std::ostream& error()
			{
				return Log<Error>();
			}

			static inline std::ostream& fatal()
			{
				return Log<Fatal>();
			}
		};
	}
}