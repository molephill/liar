
#include <core/light/BaseLight.h>

namespace Liar
{
	BaseLight::BaseLight():
		m_transform3d(new Liar::Transform3D()),
		m_color(new Liar::Vector3()),
		m_shadow(false)
	{
	}

	BaseLight::~BaseLight()
	{
		delete m_color;
		m_color = nullptr;

		delete m_transform3d;
		m_transform3d = nullptr;
	}
}