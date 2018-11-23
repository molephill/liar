#pragma once

#include <math/Matrix4x4.h>
#include "BaseCamera.h"

namespace Liar
{
	class Camera:public BaseCamera
	{
	public:
		Camera(Liar::Number nearPlane = 0.1f, Liar::Number farPlane = 1000.0f);
		virtual ~Camera();

	private:
		Liar::Viewport* m_viewPort;
		Liar::Matrix4x4* m_projectionMatrix;
		Liar::Matrix4x4* m_projectionViewMatrix;
		bool m_transformChanged;

	protected:
		virtual void CalculateProjectionMatrix();

	public:
		Liar::Viewport* GetViewPort() { return m_viewPort; };
		Liar::Matrix4x4& GetProjectionMatrix() const { return *m_projectionMatrix; };
		Liar::Matrix4x4& GetProjectionViewMatrix() const { return *m_projectionViewMatrix; };

		virtual bool Destroy(bool destroyChild = true);
		virtual Liar::Viewport& GetViewport() { return *m_viewPort; };
	};
}

