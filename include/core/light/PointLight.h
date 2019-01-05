#pragma once

#include "BaseLight.h"

namespace Liar
{
	class PointLight :public Liar::BaseLight
	{
	public:
		PointLight();
		virtual ~PointLight();

	protected:
		Liar::Number m_range;			// µã¹âµÄ·¶Î§

	public:
		void SetRange(Liar::Number value) { m_range = value; };
		Liar::Number GetRange() const { return m_range; };
		virtual bool PrepareRender(Liar::RenderState&);
	};
}