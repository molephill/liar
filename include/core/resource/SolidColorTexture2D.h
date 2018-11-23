#pragma once

#include <core/resource/Textrue2D.h>

namespace Liar
{
	class SolidColorTexture :public Liar::Texture2D
	{
	public:
		SolidColorTexture(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number a = 1.0f);
	};
}