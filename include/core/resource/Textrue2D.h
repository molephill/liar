#pragma once

#include <core/resource/BaseTexture.h>

namespace Liar
{
	class Texture2D:public Liar::BaseTeture
	{
	public:
		Texture2D(bool reapeat = true, GLint format = GL_RGBA, bool mipmap = true) :
			Liar::BaseTeture(reapeat, format, mipmap)
		{};
		~Texture2D() 
		{};

	protected:
		void SetTextureInfo()
		{
			Liar::GLContext& gl = GL::mainContext;

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
				m_memorySize *= (1 + 1.0f / 3);
			}
		};

	protected:
		void CreateGLTexture()
		{
			Liar::GLContext& gl = GL::mainContext;

			switch (m_format)
			{
			case GL_RGB:
			case GL_RGBA:
				gl.TexImage2D(m_type, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, m_data);
				break;
			}

			SetTextureInfo();
		}
	};
}