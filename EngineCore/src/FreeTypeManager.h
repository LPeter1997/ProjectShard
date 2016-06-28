#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H
#include "Patterns\Static.h"

namespace Shard
{
	class FreeTypeManager : public Patterns::Static
	{
	private:
		static bool s_Initialized;
		static FT_Library s_Library;

	public:
		static bool Initialize()
		{
			if (s_Initialized)
				return true;

			FT_Error error = FT_Init_FreeType(&s_Library);
			if (error)
				return false;
			
			return true;
		}

		static void Deinitialize()
		{
			if (!s_Initialized)
				return;
			
			FT_Done_Library(s_Library);
			s_Initialized = false;
		}

		static inline const FT_Library& GetLibrary() { return s_Library; }
	};
}