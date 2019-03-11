
#include <core/resource/shader/ShaderCompile.h>
#include <Liar3D.h>

namespace Liar
{
	ShaderCompile::ShaderCompile():
		m_shaders(nullptr), m_numberShaders(0),
		m_shaderPrograms(nullptr), m_numberShaderPragrams(0),
		m_szVersion("#version 410 core\n")
	{
		AddPreComileShader("TEST", "test2.vs", "test2.fs");
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
			m_shaders = nullptr;
			m_numberShaders = 0;
		}

		if (m_preShaders)
		{
			for (i = 0; i < m_numberPreShaders; ++i)
			{
				delete m_preShaders[i];
				m_preShaders[i] = nullptr;
			}
			free(m_preShaders);
			m_preShaders = nullptr;
			m_numberPreShaders = 0;
		}

		if (m_shaderPrograms)
		{
			for (i = 0; i < m_numberShaderPragrams; ++i)
			{
				delete m_shaderPrograms[i];
				m_shaderPrograms[i] = nullptr;
			}
			free(m_shaderPrograms);
			m_shaderPrograms = nullptr;
			m_numberShaderPragrams = 0;
		}
	}

	Liar::ShaderContent* ShaderCompile::GetShaderContent(const char* name)
	{
		for (size_t i = 0; i < m_numberShaders; ++i)
		{
			Liar::ShaderContent* tmp = m_shaders[i];
			if (tmp->Equals(name))
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
		size_t blockSize = sizeof(Liar::ShaderContent*) * m_numberShaders;
		if (m_shaders) m_shaders = (Liar::ShaderContent**)realloc(m_shaders, blockSize);
		else m_shaders = (Liar::ShaderContent**)malloc(blockSize);
		m_shaders[m_numberShaders - 1] = new Liar::ShaderContent(name, content);
	}

	Liar::PreCompileShader* ShaderCompile::GetPreCompileShader(const char* name) const
	{
		for (size_t i = 0; i < m_numberPreShaders; ++i)
		{
			Liar::PreCompileShader* tmp = m_preShaders[i];
			if (tmp->Equals(name))
			{
				return tmp;
			}
		}

		return nullptr;
	}

	void ShaderCompile::AddPreComileShader(const char* name, const char* vPath, const char* fPath)
	{
		++m_numberPreShaders;
		size_t blockSize = sizeof(Liar::PreCompileShader*) * m_numberPreShaders;
		if (m_shaders) m_preShaders = (Liar::PreCompileShader**)realloc(m_preShaders, blockSize);
		else m_preShaders = (Liar::PreCompileShader**)malloc(blockSize);
		std::string vCode = LoadGLSL(vPath);
		std::string fCode = LoadGLSL(fPath);
		m_preShaders[m_numberPreShaders - 1] = new Liar::PreCompileShader(name, vCode, fCode);
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
				tmp0 = LoadGLSL(tmp2.c_str());
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
		Liar::ShaderContent* shaderContent = GetShaderContent(path);
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
				// formatURL
				std::string formatPath = Liar::Liar3D::urlFormat->ForamtShaderURL(path);
				// open files
				shaderFile.open(formatPath);
				std::stringstream shaderStream;
				// read file's buffer contents into streams
				shaderStream << shaderFile.rdbuf();
				// close file handlers
				shaderFile.close();
				// convert stream into string
				std::string shaderContent = ParseInclude(shaderStream.str());
				AddShaderContent(path, shaderContent);
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
