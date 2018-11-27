#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <core/resource/Resource.h>
#include <math/Vector2.h>
#include <math/Vector3.h>
#include <math/Vector4.h>
#include <math/Matrix3x3.h>
#include <math/Matrix4x4.h>

namespace Liar
{
	enum LiarShaderType
	{
		SHADER_TYPE_VERTEXT = 0,
		SHADER_TYPE_FRAGMENT = 1,
		SHADER_TYPE_PROGROM = 2,
	};

	class ShaderProgram:public Resource
	{
	public:
		ShaderProgram();
		~ShaderProgram();

	private:
		unsigned int m_programId;

	public:
		void Load(const char*, const char*);
		unsigned int GetProgramId() { return m_programId; };

		void Use();
		// ------------------------------------------------------------------------
		void SetBool(const std::string&, bool value) const;
		// ------------------------------------------------------------------------
		void SetInt(const std::string&, int value) const;
		// ------------------------------------------------------------------------
		void SetFloat(const std::string&, float value) const;
		// ------------------------------------------------------------------------
		void SetVec2(const std::string&, const Liar::Vector2&) const;
		void SetVec2(const std::string&, float, float) const;
		// ------------------------------------------------------------------------
		void SetVec3(const std::string&, const Liar::Vector3&) const;
		void SetVec3(const std::string&, float, float, float) const;
		// ------------------------------------------------------------------------
		void SetVec4(const std::string&, const Liar::Vector4&) const;
		void SetVec4(const std::string&, float, float, float, float) const;
		// ------------------------------------------------------------------------
		void SetMat3(const std::string&, const Liar::Matrix3x3&) const;
		// ------------------------------------------------------------------------
		void SetMat4(const std::string&, const Liar::Matrix4x4&) const;

	private:
		void CheckCompileErrors(unsigned int, LiarShaderType);
		void LinkProgram(const char*, const char*);
		std::string LoadGLSL(const char*);
	};
}

