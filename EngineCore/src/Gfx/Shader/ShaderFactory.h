#pragma once

#include <vector>
#include "../../Patterns/Static.h"
#include "GLSLProgram.h"

namespace Shard
{
	namespace Gfx
	{
		class ShaderFactory : public Patterns::Static
		{
		private:
			static std::vector<GLSLProgram*> s_Shaders;

		public:
			static GLSLProgram& CreateShader(const std::string& vert, const std::string& frag);

			static void DisposeAll();
		};
	}
}