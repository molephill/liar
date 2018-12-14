
#include <core/render/Camera.h>

namespace Liar
{
	Camera::Camera(Liar::Number nearPlane, Liar::Number farPlane):
		Liar::BaseCamera(nearPlane, farPlane),
		m_viewPort(new Liar::Viewport()),
		m_projectionMatrix(new Liar::Matrix4x4()),
		m_projectionViewMatrix(new Liar::Matrix4x4())
	{
	}


	Camera::~Camera()
	{
		delete m_viewPort;
		delete m_projectionMatrix;
		delete m_projectionViewMatrix;
		m_viewPort = nullptr;
		m_projectionMatrix = nullptr;
		m_projectionViewMatrix = nullptr;
	}

	void Camera::CalculateProjectionMatrix()
	{
		Liar::BaseCamera::CalculateProjectionMatrix();

		bool calcProjectionViewMatrix = GetTransformChanged();

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
			Liar::Matrix4x4::Multiply(*m_projectionMatrix, m_transform3D->GetWorldMatrix(), *m_projectionViewMatrix);
			/*std::cout << m_transform3D->GetWorldMatrix() << std::endl;
			std::cout << *m_projectionMatrix << std::endl;
			std::cout << *m_projectionViewMatrix << std::endl;*/
		}

	}

}