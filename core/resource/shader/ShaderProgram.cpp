
#include <core/resource/shader/ShaderProgram.h>

namespace Liar
{

	ShaderProgram::ShaderProgram():
		Liar::Resource(),
		m_programId(0)
	{

	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_programId > 0)
		{
			glDeleteProgram(m_programId);
		}
	}

	void ShaderProgram::LinkProgram(const char* vShaderCode, const char * fShaderCode)
	{
		// 2. compile shaders
		Liar::Uint vertex, fragment;

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, GLSLShaderTypeDefine::GLSL_SHADER_VERTEXT);

		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, GLSLShaderTypeDefine::GLSL_SHADER_FRAGMENT);

		// shader Program
		m_programId = glCreateProgram();
		glAttachShader(m_programId, vertex);
		glAttachShader(m_programId, fragment);
		glLinkProgram(m_programId);
		CheckCompileErrors(m_programId, GLSLShaderTypeDefine::GLSL_SHADER_PROGROM);

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// ¼ì²â±¨´í
	void ShaderProgram::CheckCompileErrors(Liar::Uint shader, GLSLShaderTypeDefine type)
	{
		int success;
		char infoLog[512];
		if (type != GLSLShaderTypeDefine::GLSL_SHADER_PROGROM)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

	void ShaderProgram::Use()
	{
		glUseProgram(m_programId);
	}

	// utility uniform functions
	// ------------------------------------------------------------------------
	void ShaderProgram::SetInt(const std::string& name, Liar::Int value) const
	{
		glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_programId, name.c_str()), static_cast<int>(value));
	}
	// ------------------------------------------------------------------------

	void ShaderProgram::SetFloat(const std::string& name, Liar::Number value) const
	{
		glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetVec2(const std::string& name, const Liar::Vector2& value) const
	{
		SetVec2(name, value.x, value.y);
	}
	void ShaderProgram::SetVec2(const std::string& name, Liar::Number x, Liar::Number y) const
	{
		glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetVec3(const std::string& name, const Liar::Vector3& value) const
	{
		SetVec3(name, value.x, value.y, value.z);
	}
	void ShaderProgram::SetVec3(const std::string& name, Liar::Number x, Liar::Number y, Liar::Number z) const
	{
		glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetVec4(const std::string& name, const Liar::Vector4& value) const
	{
		SetVec4(name, value.x, value.y, value.z, value.w);
	}
	void ShaderProgram::SetVec4(const std::string& name, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w) const
	{
		glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetMat3(const std::string& name, const Liar::Matrix3x3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, mat.Get());
	}

	// ------------------------------------------------------------------------
	void ShaderProgram::SetMat4(const std::string&name, const Liar::Matrix4x4& m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, m.Get());
	}

}
