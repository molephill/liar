#pragma once

#include <core/resource/Resource.h>

namespace Liar
{
	class BaseTexture :public Liar::Resource
	{
	public:
		BaseTexture(bool reapeat = true, GLint format = GL_RGBA, bool mipmap = true);
		virtual ~BaseTexture();

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
		void SetRepeat(bool value);
		void SetMipMap(bool value);
	};
}