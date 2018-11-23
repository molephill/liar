
#include <core/light/DirectionLight.h>

namespace Liar
{
	DirectionLight::DirectionLight():
		Liar::BaseLight(),
		m_direction(new Liar::Vector3())
	{
	}

	DirectionLight::~DirectionLight()
	{

	}

	bool DirectionLight::Destroy(bool destroyChild)
	{
		bool destroied = Liar::BaseLight::Destroy(destroyChild);
		if (destroied)
		{
			free(m_direction);
			m_direction = nullptr;
		}
		return destroied;
	}
}