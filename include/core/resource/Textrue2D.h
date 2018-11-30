#pragma once

#include <core/resource/BaseTexture.h>

namespace Liar
{
	class Texture2D:public Liar::BaseTexture
	{
	public:
		Texture2D(bool reapeat = true, GLint format = GL_RGBA, bool mipmap = true);
		virtual ~Texture2D();

	protected:
		virtual void RecreateResource();
	};
}