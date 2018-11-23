
#include <core/light/SpotLight.h>

namespace Liar
{
	SpotLight::SpotLight():
		Liar::PointLight(),
		m_direction(new Liar::Vector3()),
		m_cutOff(0.0f), m_outerCutOff(0.0f)
	{
	}

	SpotLight::~SpotLight()
	{

	}

	bool SpotLight::Destroy(bool destroyChild)
	{
		bool destroied = Liar::PointLight::Destroy(destroyChild);
		if (destroied)
		{
			free(m_direction);
			m_direction = nullptr;
		}
		return destroied;
	}
}