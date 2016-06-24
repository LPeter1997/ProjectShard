#pragma once

#include "../Patterns/Static.h"

namespace Shard
{
	namespace Debugging
	{
		enum class LogLevel
		{
			Debug, Info, Warning, Error, Fatal
		};

		struct Debug : public Patterns::Static
		{
		public:
			static inline LogLevel GetLevel() { return LogLevel::Debug; }
			static inline const char* GetDescription() { return "<DEBUG>"; }
		};

		struct Info : public Patterns::Static
		{
		public:
			static inline LogLevel GetLevel() { return LogLevel::Info; }
			static inline const char* GetDescription() { return "<INFO>"; }
		};

		struct Warning : public Patterns::Static
		{
		public:
			static inline LogLevel GetLevel() { return LogLevel::Warning; }
			static inline const char* GetDescription() { return "<WARNING>"; }
		};

		struct Error : public Patterns::Static
		{
		public:
			static inline LogLevel GetLevel() { return LogLevel::Error; }
			static inline const char* GetDescription() { return "<ERROR>"; }
		};

		struct Fatal : public Patterns::Static
		{
		public:
			static inline LogLevel GetLevel() { return LogLevel::Fatal; }
			static inline const char* GetDescription() { return "<FATAL>"; }
		};
	}
}