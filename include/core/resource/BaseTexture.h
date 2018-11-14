#pragma once

#include <core/resource/Resource.h>
#include <core/GL.h>
#include <math/MathUtils3D.h>

namespace Liar
{
	class BaseTeture :public Liar::Resource
	{
	public:
		BaseTeture(bool reapeat = true, GLint format = GL_RGBA, bool mipmap = true) :
			Liar::Resource(),
			m_type(GL_TEXTURE_2D),
			m_width(0), m_height(0),
			m_repeat(reapeat), m_mipmap(mipmap),
			m_format(format),
			m_minFifter(-1), m_magFifter(-1),
			m_data(nullptr)
		{};
		virtual ~BaseTeture()
		{};

	protected:
		GLenum m_type;
		Liar::Uint m_width;
		Liar::Uint m_height;
		bool m_repeat;
		bool m_mipmap;
		Liar::Int m_format;
		GLint m_minFifter;
		GLint m_magFifter;
		Liar::UChar* m_data;

	public:
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		bool GetRepeat() const { return m_repeat; };
		bool GetMipmap() const { return m_mipmap; };
		Liar::Uint GetFormat() const { return m_format; };

	public:
		void SetRepeat(bool value)
		{
			if (m_repeat != value)
			{
				m_repeat = value;
				bool isPot = Liar::MathUtils3D::IsPOT(m_width, m_height);
				Liar::GLContext& gl = GL::mainContext;
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

		void SetMipMap(bool value)
		{
			if (m_mipmap != value)
			{
				m_mipmap = value;
			}
		}
	};
}