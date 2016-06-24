#pragma once

namespace Shard
{
	namespace Patterns
	{
		template <typename T>
		class Singleton
		{
		public:
			static T& Get()
			{
				static T instance;
				return instance;
			}

		private:
			Singleton() {}

			// Don't implement
			Singleton(Singleton const&);
			void operator=(Singleton const&);

		public:
			Singleton(Singleton const&) = delete;
			void operator=(Singleton const&) = delete;
		};
	}
}