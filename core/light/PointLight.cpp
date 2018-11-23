
#include <core/light/PointLight.h>

namespace Liar
{
	PointLight::PointLight():
		Liar::BaseLight(),
		m_constant(0.0f), m_linear(0.0f), m_quadratic(0.0f)
	{
	}

	PointLight::~PointLight()
	{

	}
}