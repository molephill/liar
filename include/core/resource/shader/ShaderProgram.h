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
#include <core/resource/shader/ShaderDefine.h>

namespace Liar
{
	class ShaderProgram:public Resource
	{
	public:
		ShaderProgram();
		~ShaderProgram();

	private:
		Liar::Uint m_programId;

	public:
		void LinkProgram(const char*, const char*);
		Liar::Uint GetProgramId() { return m_programId; };

		void Use();
		// ------------------------------------------------------------------------
		void SetBool(const std::string&, bool value) const;
		// ------------------------------------------------------------------------
		void SetInt(const std::string&, Liar::Int value) const;
		// ------------------------------------------------------------------------
		void SetFloat(const std::string&, Liar::Number value) const;
		// ------------------------------------------------------------------------
		void SetVec2(const std::string&, const Liar::Vector2&) const;
		void SetVec2(const std::string&, Liar::Number, Liar::Number) const;
		// ------------------------------------------------------------------------
		void SetVec3(const std::string&, const Liar::Vector3&) const;
		void SetVec3(const std::string&, Liar::Number, Liar::Number, Liar::Number) const;
		// ------------------------------------------------------------------------
		void SetVec4(const std::string&, const Liar::Vector4&) const;
		void SetVec4(const std::string&, Liar::Number, Liar::Number, Liar::Number, Liar::Number) const;
		// ------------------------------------------------------------------------
		void SetMat3(const std::string&, const Liar::Matrix3x3&) const;
		// ------------------------------------------------------------------------
		void SetMat4(const std::string&, const Liar::Matrix4x4&) const;

	private:
		void CheckCompileErrors(Liar::Uint, GLSLShaderTypeDefine);
	};
}

