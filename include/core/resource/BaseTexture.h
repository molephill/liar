#pragma once

#include <core/resource/Resource.h>
#include <stb_image.h>
#include <string>
#include <algorithm>

namespace Liar
{
	class BaseTexture :public Liar::Resource
	{
	public:
		BaseTexture(bool reapeat = true, GLint format = GL_RGBA, bool mipmap = true);
		virtual ~BaseTexture();

	protected:
		GLenum m_type;
		Liar::Int m_width;
		Liar::Int m_height;
		bool m_repeat;
		bool m_mipmap;
		Liar::Int m_format;
		GLint m_minFifter;
		GLint m_magFifter;
		Liar::UChar* m_data;
		std::string m_url;
		Liar::Uint m_textureID;

	public:
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		bool GetRepeat() const { return m_repeat; };
		bool GetMipmap() const { return m_mipmap; };
		Liar::Uint GetFormat() const { return m_format; };
		Liar::Uint GetTextureID() const { return m_textureID; };
		virtual void SetURL(const char*);

	protected:
		virtual void DisposeResource();
		virtual void RecreateResource();

	public:
		void SetRepeat(bool value);
		void SetMipMap(bool value);
	};
}