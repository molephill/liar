
#include <core/resource/shader/ShaderCompile.h>
#include <Liar3D.h>

namespace Liar
{
	ShaderCompile::ShaderCompile():
		m_shaders(nullptr), m_numberShaders(0)
	{
	}


	ShaderCompile::~ShaderCompile()
	{
		size_t i = 0;
		if (m_shaders)
		{
			for (i = 0; i < m_numberShaders; ++i)
			{
				delete m_shaders[i];
				m_shaders[i] = nullptr;
			}
			free(m_shaders);
			m_numberShaders = 0;
		}
	}

	Liar::ShaderContent* ShaderCompile::GetShaderContent(const char* name)
	{
		for (size_t i = 0; i < m_numberShaders; ++i)
		{
			Liar::ShaderContent* tmp = m_shaders[i];
			if (strcmp(tmp->name.c_str(), name) == 0)
			{
				return tmp;
			}
		}

		return nullptr;
	}

	void ShaderCompile::AddShaderContent(const std::string& name, const std::string& content)
	{
		if (strcmp(name.c_str(), "") == 0 || strcmp(content.c_str(), "") == 0) return;
		++m_numberShaders;
		if (m_shaders)
		{
			m_shaders = (Liar::ShaderContent**)realloc(m_shaders, sizeof(Liar::ShaderContent*) * m_numberShaders);
		}
		else
		{
			m_shaders = (Liar::ShaderContent**)malloc(sizeof(Liar::ShaderContent*) * m_numberShaders);
		}
		m_shaders[m_numberShaders - 1] = new Liar::ShaderContent(name, content);
	}

	/*
	*	解析头文件
	*/
	std::string ShaderCompile::ParseInclude(std::string content)
	{
		std::string head, other;
		Liar::StringParse::SplitHeadAndLast(content, head, other, "#include");

		if (strcmp(other.c_str(), "") == 0)
		{
			return content;
		}
		else
		{
			std::string tmp0, tmp1;
			std::string tmp2 = Liar::StringParse::GetRange(other, tmp1);

			Liar::ShaderContent* tmp = GetShaderContent(tmp2.c_str());
			if (!tmp)
			{
				tmp0 = Liar::Liar3D::basePath;
				tmp0 += "resource/shader/files/";
				tmp0 += tmp2;

				tmp0 = LoadGLSL(tmp0.c_str());
				content = head + tmp0 + tmp1;
			}
			else
			{
				content = head + tmp->content + tmp1;
			}

			return ParseInclude(content);
		}
	}

	std::string ShaderCompile::LoadGLSL(const char* path)
	{
		std::string shaderName = Liar::StringParse::GetLast(path, "/");
		Liar::ShaderContent* shaderContent = GetShaderContent(shaderName.c_str);
		if (shaderContent)
		{
			return shaderContent->content;
		}
		else
		{
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				// open files
				shaderFile.open(path);
				std::stringstream shaderStream;
				// read file's buffer contents into streams
				shaderStream << shaderFile.rdbuf();
				// close file handlers
				shaderFile.close();
				// convert stream into string
				std::string shaderContent = ParseInclude(shaderStream.str());
				AddShaderContent(shaderName, shaderContent);
				return shaderContent;
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
				return "";
			}
		}
	}

	const char* ShaderCompile::GetShaderDefineChar(Liar::ShaderTypeDefine type) const
	{
		switch (type)
		{
		case Liar::ShaderTypeDefine::SHADERTYPE_ALPHATEST:
			return "ALPHATEST";
		case Liar::ShaderTypeDefine::SHADERTYPE_DIFFUSEMAP:
			return "DIFFUSEMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_NORMALMAP:
			return "NORMALMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_SPECULARMAP:
			return "SPECULARMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_EMISSIVEMAP:
			return "EMISSIVEMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_REFLECTMAP:
			return "REFLECTMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_UVTRANSFORM:
			return "UVTRANSFORM";
		case Liar::ShaderTypeDefine::SHADERTYPE_TILINGOFFSET:
			return "TILINGOFFSET";
		case Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG:
			return "ADDTIVEFOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_HIGHPRECISION:
			return "HIGHPRECISION";
		case Liar::ShaderTypeDefine::SHADERTYPE_FOG:
			return "FOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_DIRECTIONLIGHT:
			return "DIRECTIONLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_POINTLIGHT:
			return "POINTLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_SPOTLIGHT:
			return "SPOTLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_UV0:
			return "UV0";
		case Liar::ShaderTypeDefine::SHADERTYPE_COLOR:
			return "COLOR";
		case Liar::ShaderTypeDefine::SHADERTYPE_UV1:
			return "UV1";
		case Liar::ShaderTypeDefine::SHADERTYPE_DEPTHFOG:
			return "DEPTHFOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_RECEIVE_SHADOW:
			return "RECEIVE_SHADOW";
		case Liar::ShaderTypeDefine::SHADERTYPE_CAST_SHADOW:
			return "CAST_SHADOW";
		default:
			return nullptr;
		}
	}
}
