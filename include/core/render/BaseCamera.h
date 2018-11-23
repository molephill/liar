#pragma once

#include <core/display/TransformNode.h>
#include <math/Viewport.h>

namespace Liar
{
	class BaseCamera:public TransformNode
	{
	public:
		BaseCamera(Liar::Number nearPlane = 0.1f, Liar::Number farPlane = 1000.0f);
		virtual ~BaseCamera();

	protected:
		Liar::Number m_nearPlane;
		Liar::Number m_farPlane;
		Liar::Number m_fieldOfView;
		Liar::Number m_orthographicVerticalSize;

		bool m_orthographic;

	protected:
		virtual void CalculateProjectionMatrix() {};

	public:
		Liar::Number GetNearPlane() const { return m_nearPlane; };
		Liar::Number GetFarPlane() const { return m_farPlane; };
		Liar::Number GetFieldOfView() const { return m_fieldOfView; };
		bool GetOrthographic() const { return m_orthographic; };

		void SetNearPlane(Liar::Number);
		void SetFarPlane(Liar::Number);
		void SetFieldOfView(Liar::Number);
		void SetOrthograpic(bool);

		virtual Liar::Viewport& GetViewport() = 0;
	};
}