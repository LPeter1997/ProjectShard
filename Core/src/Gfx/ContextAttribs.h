#pragma once

#include <string>
#include "../Types.h"

namespace Shard
{
	namespace Gfx
	{
		struct ContextAttribs
		{
			// Dimensions
			uint Width;
			uint Height;
			// Title or name
			std::string Title;
		};
	}
}