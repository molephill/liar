
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
		m_data(nullptr)
	{
	}

	BaseTexture::~BaseTexture()
	{

	}

	void BaseTexture::SetRepeat(bool value)
	{
		if (m_repeat != value)
		{
			m_repeat = value;
			bool isPot = Liar::MathUtils3D::IsPOT(m_width, m_height);
			Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
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
}