
#include <core/render/Camera.h>

namespace Liar
{
	Camera::Camera(Liar::Number nearPlane, Liar::Number farPlane):
		Liar::BaseCamera(nearPlane, farPlane),
		m_viewPort(new Liar::Viewport()),
		m_projectionMatrix(new Liar::Matrix4x4()),
		m_projectionViewMatrix(new Liar::Matrix4x4()),
		m_transformChanged(true)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::CalculateProjectionMatrix()
	{
		bool calcProjectionViewMatrix = m_transformChanged || m_transform3D->GetTransformChanged();

		if (m_transformChanged)
		{
			m_transformChanged = false;

			if (m_orthographic)
			{
				Liar::Number halfWidth = m_orthographicVerticalSize * m_viewPort->GetAspect() * 0.5f;
				Liar::Number halfHeight = m_orthographicVerticalSize * 0.5f;
				Liar::Matrix4x4::CreateOrthoOffCenterRH(
					-halfWidth, 
					halfWidth, 
					-halfHeight, 
					halfHeight, 
					m_nearPlane, 
					m_farPlane, 
					*m_projectionMatrix
				);
			}
			else
			{
				Liar::Matrix4x4::CreatePerspective(
					Liar::MathUtils3D::RandinToAngle * m_fieldOfView,
					m_viewPort->GetAspect(),
					m_nearPlane,
					m_farPlane,
					*m_projectionMatrix
				);
			}
		}

		if (calcProjectionViewMatrix)
		{
			Liar::Matrix4x4::Multiply(*m_projectionMatrix, m_transform3D->GetMatrix(), *m_projectionViewMatrix);
		}
	}

	bool Camera::Destroy(bool destroyChild)
	{
		bool destroied = Liar::TransformNode::Destroy(destroyChild);
		if (destroied)
		{
			free(m_viewPort);
			free(m_projectionMatrix);
			free(m_projectionViewMatrix);
			m_viewPort = nullptr;
			m_projectionMatrix = nullptr;
			m_projectionViewMatrix = nullptr;
		}
		return destroied;
	}

}