
#include <core/light/BaseLight.h>

namespace Liar
{
	BaseLight::BaseLight():
		m_color(new Liar::Vector3()),
		m_shadow(false)
	{
	}

	BaseLight::~BaseLight()
	{
		Destroy();
	}

	bool BaseLight::Destroy(bool destroyChild)
	{
		delete m_color;
		m_color = nullptr;
		return true;
	}
}