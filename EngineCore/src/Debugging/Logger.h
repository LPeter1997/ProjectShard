#pragma once

#include <ostream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "../Patterns/Static.h"
#include "LogLevel.h"

namespace Shard
{
	namespace Debugging
	{
		class Logger : public Patterns::Static
		{
		private:
			static std::ostream& s_Ostream;

		public:
			template <typename Level>
			static inline std::ostream& Log()
			{
				auto t = std::time(nullptr);
				auto tm = *std::localtime(&t);
				return s_Ostream << '[' << std::put_time(&tm, "%H-%M-%S") << "] " << Level::GetDescription() << ' ' << (unsigned int)Level::GetLevel() << ": ";
			}
		};

		std::ostream& Logger::s_Ostream = std::cout;
	}
}