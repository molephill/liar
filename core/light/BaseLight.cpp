
#include <core/light/BaseLight.h>

namespace Liar
{
	BaseLight::BaseLight():
		Liar::Node(),
		m_color(new Liar::Vector3()),
		m_ambient(new Liar::Vector3()),
		m_diffuse(new Liar::Vector3()),
		m_specular(new Liar::Vector3()),
		m_shadow(false)
	{
	}

	BaseLight::~BaseLight()
	{

	}

	bool BaseLight::Destroy(bool destroyChild)
	{
		bool destroied = Liar::Node::Destroy(destroyChild);
		if (destroied)
		{
			free(m_color);
			free(m_ambient);
			free(m_diffuse);
			free(m_specular);
			m_color = nullptr;
			m_ambient = nullptr;
			m_diffuse = nullptr;
			m_specular = nullptr;
		}
		return destroied;
	}
}