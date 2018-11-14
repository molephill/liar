#pragma once

#include <display/Node.h>
#include <core/Transform3D.h>

namespace Liar
{
	class BaseCamera:public Node
	{
	public:
		BaseCamera(Liar::Number nearPlane = 0.1f, Liar::Number farPlane = 1000.0f);
		virtual ~BaseCamera();

	protected:
		Liar::Transform3D* m_transform3D;

		Liar::Number m_nearPlane;
		Liar::Number m_farPlane;
		Liar::Number m_fieldOfView;
		Liar::Number m_orthographicVerticalSize;

		bool m_orthographic;
		bool m_transformChanged;

	protected:
		virtual void CalculateProjectionMatrix() {};

	public:
		Liar::Number GetNearPlane() const { return m_nearPlane; };
		Liar::Number GetFarPlane() const { return m_farPlane; };
		Liar::Number GetFieldOfView() const { return m_fieldOfView; };
		Liar::Transform3D& GetTransform3D() const { return *m_transform3D; };
		bool GetOrthographic() const { return m_orthographic; };

		void SetNearPlane(Liar::Number);
		void SetFarPlane(Liar::Number);
		void SetFieldOfView(Liar::Number);
		void SetOrthograpic(bool);
	};
}