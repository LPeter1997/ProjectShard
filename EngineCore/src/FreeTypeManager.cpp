#include "FreeTypeManager.h"

namespace Shard
{
	bool FreeTypeManager::s_Initialized = false;
	FT_Library FreeTypeManager::s_Library;
}