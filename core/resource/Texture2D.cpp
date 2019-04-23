
#include <core/resource/Textrue2D.h>
#include <math/MathUtils3D.h>
#include <Liar3D.h>

namespace Liar
{
	Texture2D::Texture2D(bool reapeat, GLint format, bool mipmap):
		Liar::BaseTexture(reapeat, format, mipmap)
	{
	}

	Texture2D::~Texture2D()
	{
	}

	void Texture2D::RecreateResource()
	{
		Liar::BaseTexture::RecreateResource();

		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);

		switch (m_format)
		{
		case GL_RGB:
		case GL_RGBA:
			gl.TexImage2D(m_type, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, m_data);
			break;
		}

		GLint repeat = m_repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;
		bool isPot = Liar::MathUtils3D::IsPOT(m_width, m_height);

		GLint minFifter = m_minFifter;
		GLint magFifter = m_magFifter;

		if (isPot)
		{
			if (minFifter == -1) minFifter = m_mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
			if (magFifter == -1) magFifter = GL_LINEAR;

			gl.TexParameteri(m_type, GL_TEXTURE_MIN_FILTER, minFifter);
			gl.TexParameteri(m_type, GL_TEXTURE_MAG_FILTER, magFifter);
		}
		else
		{
			if (minFifter == -1) minFifter = GL_LINEAR;
			if (magFifter == -1) magFifter = GL_LINEAR;
		}

		gl.TexParameteri(m_type, GL_TEXTURE_WRAP_S, repeat);
		gl.TexParameteri(m_type, GL_TEXTURE_WRAP_T, repeat);

		m_memorySize = m_width * m_height * 4;
		if (isPot && m_mipmap)
		{
			gl.GenerateMipmap(m_type);
			m_memorySize *= (1 + 1 / 3);
		}
	}
}