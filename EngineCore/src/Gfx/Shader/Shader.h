#pragma once

#include <GL\glew.h>
#include <string>
#include <vector>
#include "../../Types.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		class Shader
		{
		private:
			GLenum m_Type;
			GLuint m_ShaderID;
			std::string m_Source;
			bool m_Compiled;

		public:
			Shader(GLenum type, const std::string& src)
				: m_Type(type), m_Source(src), m_Compiled(false), m_ShaderID(0)
			{
			}

			virtual ~Shader()
			{
				Dispose();
			}

			bool Compile()
			{
				if (m_Compiled)
					return true;

				m_ShaderID = glCreateShader(m_Type);
				const char *src = m_Source.c_str();
				glShaderSource(m_ShaderID, 1, &src, NULL);
				glCompileShader(m_ShaderID);

				GLint result;
				glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);

				// Compile error
				if (result == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(m_ShaderID, length, &length, &error[0]);
					Debugging::Logger::Log<Debugging::Error>() << "Failed to compile shader: " << &error[0] << std::endl;
					glDeleteShader(m_ShaderID);
					m_ShaderID = 0;
					return false;
				}

				Debugging::Logger::Log<Debugging::Info>() << "Shader compiled successfully!" << std::endl;
				m_Compiled = true;
				return true;
			}

			void Dispose()
			{
				if (!m_Compiled)
					return;

				glDeleteShader(m_ShaderID);
				m_Source.clear();
				m_ShaderID = 0;
			}

			inline bool IsCompiled() const { return m_Compiled; }
			inline GLuint GetShaderID() const { return m_ShaderID; }
		};

		// Wrapper to make different shader definitions easier
		template <GLenum type>
		class TypedShader : public Shader
		{
		public:
			TypedShader(const std::string& src)
				: Shader(type, src)
			{
			}
		};

		typedef TypedShader<GL_VERTEX_SHADER> VertexShader;
		typedef TypedShader<GL_FRAGMENT_SHADER> FragmentShader;
	}
}