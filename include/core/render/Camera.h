#pragma once

#include <math/Matrix4x4.h>
#include "BaseCamera.h"

namespace Liar
{
	class Camera:public BaseCamera
	{
	public:
		Camera(Liar::Number nearPlane = 0.1f, Liar::Number farPlane = 100.0f);
		virtual ~Camera();

	private:
		Liar::Viewport* m_viewPort;
		Liar::Matrix4x4* m_projectionMatrix;
		Liar::Matrix4x4* m_projectionViewMatrix;

	protected:
		virtual void CalculateProjectionMatrix();

	public:
		Liar::Viewport* GetViewPort() { return m_viewPort; };
		Liar::Matrix4x4& GetProjectionMatrix() const { return *m_projectionMatrix; };
		Liar::Matrix4x4& GetProjectionViewMatrix() const { return *m_projectionViewMatrix; };
		virtual Liar::Viewport& GetViewport() { return *m_viewPort; };
	};
}

