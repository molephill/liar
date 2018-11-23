#include <core/render/BaseCamera.h>

namespace Liar
{
	BaseCamera::BaseCamera(Liar::Number nearPlane, Liar::Number farPlane):
		Liar::TransformNode(),
		m_nearPlane(nearPlane), m_farPlane(farPlane),
		m_orthographic(false), m_fieldOfView(60.f),
		m_orthographicVerticalSize(10.0f)
	{
	}

	BaseCamera::~BaseCamera()
	{
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
