#pragma once

namespace Shard
{
	namespace Patterns
	{
		class Static
		{
		private:
			virtual void __disallow_creation() = 0;
		};
	}
}