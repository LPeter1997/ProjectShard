#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GLSLProgram.h"
#include "../../Debugging/Logger.h"

namespace Shard
{
	namespace Gfx
	{
		GLSLProgram::GLSLProgram()
			: m_Linked(false)
		{
			m_ProgramID = glCreateProgram();
		}

		GLSLProgram::~GLSLProgram()
		{
			Dispose();
		}
		
		bool GLSLProgram::Link()
		{
			if (m_Linked)
				return true;

			glLinkProgram(m_ProgramID);

			GLint success;
			glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
			if (success == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetProgramInfoLog(m_ProgramID, length, &length, &error[0]);
				Debugging::Logger::Log<Debugging::Error>() << "Failed to link program: " << std::string(&error[0]) << std::endl;
				DetachAllShaders();
				return false;
			}

			glValidateProgram(m_ProgramID);
			glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &success);
			if (success == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetProgramInfoLog(m_ProgramID, length, &length, &error[0]);
				Debugging::Logger::Log<Debugging::Error>() << "Failed to validate program: " + std::string(&error[0]) << std::endl;
				DetachAllShaders();
				return false;
			}

			Debugging::Logger::Log<Debugging::Info>() << "GLSL program successfully compiled!" << std::endl;

			DetachAllShaders();
			m_Linked = true;
			return true;
		}

		void GLSLProgram::Dispose()
		{
			DetachAllShaders();

			if (!m_Linked)
				return;

			glDeleteProgram(m_ProgramID);
			m_ProgramID = 0;
		}

		void GLSLProgram::AddShader(Shader& shader)
		{
			if (!shader.IsCompiled())
				shader.Compile();

			glAttachShader(m_ProgramID, shader.GetShaderID());
			m_Shaders.push_back(&shader);
		}

		void GLSLProgram::DetachAllShaders()
		{
			for (Shader* sh : m_Shaders)
				glDetachShader(m_ProgramID, sh->GetShaderID());

			m_Shaders.clear();
		}
	}
}