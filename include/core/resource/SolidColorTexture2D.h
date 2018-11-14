#pragma once

#include <core/resource/Textrue2D.h>

namespace Liar
{
	class SolidColorTexture :public Liar::Texture2D
	{
	public:
		SolidColorTexture(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number a = 1.0f):
			Liar::Texture2D()
		{
			m_width = 1;
			m_height = 1;
			m_data = (Liar::UChar*)malloc(sizeof(Liar::UChar) * 4);
			m_data[0] = static_cast<Liar::UChar>(r * 255);
			m_data[1] = static_cast<Liar::UChar>(g * 255);
			m_data[2] = static_cast<Liar::UChar>(b * 255);
			m_data[3] = static_cast<Liar::UChar>(a * 255);
		};
	};
}