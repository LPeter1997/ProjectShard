#pragma once

#include <GLFW\glfw3.h>
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/Vector3.h"
#include "../../Maths/Vector4.h"
#include "../../Maths/Matrix.h"

namespace Shard
{
	namespace Gfx
	{
		class GLSLProgram
		{
		private:
			GLuint m_ProgramID;
			std::vector<Shader*> m_Shaders;
			bool m_Linked;

		public:
			GLSLProgram();
			~GLSLProgram();

			void AddShader(Shader& shader);
			void Dispose();

			bool Link();

			inline void Enable() const { glUseProgram(m_ProgramID); }
			inline void Disable() const { glUseProgram(0); }
			inline bool IsLinked() const { return m_Linked; }

		private:
			void DetachAllShaders();

			inline GLint GLSLProgram::GetUniformLocation(const GLchar * name) const
			{
				return glGetUniformLocation(m_ProgramID, name);
			}

		public:
			// Uniforms
			inline void SetUniform1d(const GLchar * name, double value) const
			{
				glUniform1d(GetUniformLocation(name), value);
			}

			inline void SetUniform1f(const GLchar * name, float value) const
			{
				glUniform1f(GetUniformLocation(name), value);
			}

			inline void SetUniform1i(const GLchar * name, int value) const
			{
				glUniform1i(GetUniformLocation(name), value);
			}

			inline void SetUniform1fv(const GLchar * name, float * value, GLsizei count) const
			{
				glUniform1fv(GetUniformLocation(name), count, value);
			}

			inline void SetUniform1iv(const GLchar * name, int * value, GLsizei count) const
			{
				glUniform1iv(GetUniformLocation(name), count, value);
			}

			inline void SetUniform2d(const GLchar * name, const Maths::Vector2d& vector) const
			{
				glUniform2d(GetUniformLocation(name), vector.x, vector.y);
			}

			inline void SetUniform2f(const GLchar * name, const Maths::Vector2f& vector) const
			{
				glUniform2f(GetUniformLocation(name), vector.x, vector.y);
			}

			inline void SetUniform2i(const GLchar * name, const Maths::Vector2i& vector) const
			{
				glUniform2i(GetUniformLocation(name), vector.x, vector.y);
			}

			inline void SetUniform3d(const GLchar * name, const Maths::Vector3d& vector) const
			{
				glUniform3d(GetUniformLocation(name), vector.x, vector.y, vector.z);
			}

			inline void SetUniform3f(const GLchar * name, const Maths::Vector3f& vector) const
			{
				glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
			}

			inline void SetUniform3i(const GLchar * name, const Maths::Vector3i& vector) const
			{
				glUniform3i(GetUniformLocation(name), vector.x, vector.y, vector.z);
			}

			inline void SetUniform4d(const GLchar * name, const Maths::Vector4d& vector) const
			{
				glUniform4d(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
			}

			inline void SetUniform4f(const GLchar * name, const Maths::Vector4f& vector) const
			{
				glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
			}

			inline void SetUniform4i(const GLchar * name, const Maths::Vector4i& vector) const
			{
				glUniform4i(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
			}

			inline void SetUniformMat4f(const GLchar * name, const Maths::Matrix4f& matrix) const
			{
				glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.Elements);
			}

			// Attribs
			inline void BindAttribute(GLuint index, const std::string& name) const
			{
				glBindAttribLocation(m_ProgramID, index, name.c_str());
			}
		};
	}
}