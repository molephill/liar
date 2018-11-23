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
		Liar::Number m_constant;
		Liar::Number m_linear;
		Liar::Number m_quadratic;

	public:
		void SetConstant(Liar::Number value) { m_constant = value; };
		void SetLinear(Liar::Number value) { m_linear = value; };
		void SetQuadratic(Liar::Number value) { m_quadratic = value; };

		Liar::Number GetConstant() const { return m_constant; };
		Liar::Number GetLinear() const { return m_linear; };
		Liar::Number GetQuadratic() const { return m_quadratic; };
	};
}