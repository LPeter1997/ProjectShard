#include <GL/glew.h>
#include "ShaderFactory.h"

namespace Shard
{
	namespace Gfx
	{
		std::vector<GLSLProgram*> ShaderFactory::s_Shaders;

		GLSLProgram& ShaderFactory::CreateShader(const std::string& vert, const std::string& frag)
		{
			GLSLProgram* prg = new GLSLProgram();
			VertexShader vs(vert);
			FragmentShader fs(frag);
			prg->AddShader(vs);
			prg->AddShader(fs);
			prg->Link();
			return *prg;
		}

		void ShaderFactory::DisposeAll()
		{
			for (GLSLProgram* prg : s_Shaders)
				delete prg;
		}
	}
}