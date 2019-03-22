
#include <core/resource/BaseTexture.h>
#include <Liar3D.h>

namespace Liar
{
	BaseTexture::BaseTexture(bool reapeat, GLint format, bool mipmap):
		Liar::Resource(),
		m_repeat(reapeat), m_mipmap(format), m_format(format),
		m_type(GL_TEXTURE_2D),
		m_width(0), m_height(0),
		m_minFifter(-1), m_magFifter(-1),
		m_data(nullptr), m_url(""), m_textureID(0)
	{
	}

	BaseTexture::~BaseTexture()
	{
		if (Destroy())
		{
			Liar::Liar3D::mtl->DelShareTexture(this);
		}
	}

	void BaseTexture::SetURL(const char* url)
	{
		if (strcmp(url, m_url.c_str()) != 0)
		{
			ReleaseResource();
			m_url = url;
			std::string formatPath = Liar3D::urlFormat->FormatSourceURL(url);

			int nrComponents = 0;
			m_data = stbi_load(formatPath.c_str(), &m_width, &m_height, &nrComponents, 0);
			if (m_data)
			{
				m_loaded = true;
				switch (nrComponents)
				{
				case 1:
					m_format = GL_RED;
					break;
				case 4:
					m_format = GL_RGBA;
					break;
				case 3:
				default:
					m_format = GL_RGB;
					break;
				}
				ActiveResource();
			}
		}
	}

	void BaseTexture::RecreateResource()
	{
		Liar::Resource::RecreateResource();
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void BaseTexture::SetRepeat(bool value)
	{
		if (m_repeat != value)
		{
			m_repeat = value;
			bool isPot = Liar::MathUtils3D::IsPOT(m_width, m_height);
			Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
			if (isPot && m_repeat) {
				gl.TexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
				gl.TexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			}
			else {
				gl.TexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				gl.TexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
		}
	}

	void BaseTexture::SetMipMap(bool value)
	{
		if (m_mipmap != value)
		{
			m_mipmap = value;
		}
	}

	void BaseTexture::DisposeResource()
	{
		if (m_data) free(m_data);
		m_released = true;
		if(m_textureID > 0) glDeleteTextures(1, &m_textureID);
	}

	void BaseTexture::Draws(Liar::ShaderProgram& shader, Liar::Int index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		shader.SetInt("material.diffuse", index);
	}
}