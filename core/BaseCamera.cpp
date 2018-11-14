#include <core/BaseCamera.h>

namespace Liar
{
	BaseCamera::BaseCamera(Liar::Number nearPlane, Liar::Number farPlane):
		Liar::Node(),
		m_transform3D(new Liar::Transform3D()),
		m_nearPlane(nearPlane), m_farPlane(m_farPlane),
		m_orthographic(false), m_transformChanged(true),
		m_fieldOfView(60.0f), m_orthographicVerticalSize(10.0f)
	{
	}


	BaseCamera::~BaseCamera()
	{
		delete m_transform3D;
	}

	void BaseCamera::SetFarPlane(Liar::Number value)
	{
		if (m_farPlane != value)
		{
			m_farPlane = value;
			m_transformChanged = true;
		}
	}

	void BaseCamera::SetNearPlane(Liar::Number value)
	{
		if (m_nearPlane != value)
		{
			m_nearPlane = value;
			m_transformChanged = true;
		}
	}

	void BaseCamera::SetFieldOfView(Liar::Number value)
	{
		if (m_fieldOfView != value)
		{
			m_fieldOfView = value;
			m_transformChanged = true;
		}
	}

	void BaseCamera::SetOrthograpic(bool value)
	{
		if (m_orthographic != value)
		{
			m_orthographic = value;
			m_transformChanged = true;
		}
	}

}
