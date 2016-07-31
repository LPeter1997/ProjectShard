#pragma once

namespace Shard
{
	namespace Debugging
	{
		enum class LogLevel
		{
			Debug, Info, Warning, Error, Fatal
		};

		struct Debug
		{
		private:
			Debug() = delete;

		public:
			static inline LogLevel GetLevel() { return LogLevel::Debug; }
			static inline const char* GetDescription() { return "<DEBUG>"; }
		};

		struct Info
		{
		private:
			Info() = delete;

		public:
			static inline LogLevel GetLevel() { return LogLevel::Info; }
			static inline const char* GetDescription() { return "<INFO>"; }
		};

		struct Warning
		{
		private:
			Warning() = delete;

		public:
			static inline LogLevel GetLevel() { return LogLevel::Warning; }
			static inline const char* GetDescription() { return "<WARNING>"; }
		};

		struct Error
		{
		private:
			Error() = delete;

		public:
			static inline LogLevel GetLevel() { return LogLevel::Error; }
			static inline const char* GetDescription() { return "<ERROR>"; }
		};

		struct Fatal
		{
		private:
			Fatal() = delete;

		public:
			static inline LogLevel GetLevel() { return LogLevel::Fatal; }
			static inline const char* GetDescription() { return "<FATAL>"; }
		};
	}
}