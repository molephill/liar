#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <LiarType.h>
#include <utils/StringParse.h>
#include <core/resource/shader/ShaderProgram.h>

namespace Liar
{
	class ShaderContent
	{
	public:
		ShaderContent(const std::string& n, const std::string& c) :name(n), content(c) {};
		std::string name;
		std::string content;

		bool Equals(const char* n) const { return name == n; };
	};

	class PreCompileShader
	{
	public:
		PreCompileShader(const char* n, const std::string& vCode, const std::string& fCode) : name(n), vertexShaderCode(vCode), fragmentShaderCode(fCode) {};
		std::string name;
		std::string vertexShaderCode;
		std::string fragmentShaderCode;

		bool Equals(const char* n) const { return name == n; };
	};

	class ShaderCompile
	{
	public:
		ShaderCompile();
		~ShaderCompile();

	private:
		Liar::ShaderContent** m_shaders;
		Liar::Uint m_numberShaders;

		Liar::PreCompileShader** m_preShaders;
		Liar::Uint m_numberPreShaders;

		Liar::ShaderProgram** m_shaderPrograms;
		Liar::Uint m_numberShaderPragrams;

		const char* m_szVersion;

	private:
		const char* GetShaderDefineChar(Liar::ShaderTypeDefine) const;

		Liar::ShaderContent* GetShaderContent(const char*);
		void AddShaderContent(const std::string&, const std::string&);
		void AddPreComileShader(const char*, const char*, const char*);
		std::string ParseInclude(std::string);
		std::string LoadGLSL(const char*);

	public:
		std::string GetVersion() const { return m_szVersion; };
		Liar::PreCompileShader* GetPreCompileShader(const char*) const;
	};
}

