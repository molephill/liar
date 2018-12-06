#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <core/resource/shader/ShaderDefine.h>
#include <LiarType.h>
#include <utils/StringParse.h>

namespace Liar
{
	class ShaderContent
	{
	public:
		ShaderContent(const std::string& n, const std::string& c) :name(n), content(c) {};
		std::string name;
		std::string content;
	};

	class ShaderCompile
	{
	public:
		ShaderCompile();
		~ShaderCompile();

	private:
		Liar::ShaderContent** m_shaders;
		Liar::Uint m_numberShaders;

	private:
		const char* GetShaderDefineChar(Liar::ShaderTypeDefine) const;
		Liar::ShaderContent* GetShaderContent(const char*);
		void AddShaderContent(const std::string&, const std::string&);
		std::string ParseInclude(std::string);

	public:
		std::string LoadGLSL(const char*);
	};
}

