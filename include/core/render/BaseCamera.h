#pragma once

#include <core/display/Node.h>
#include <math/Viewport.h>
#include <core/render/RenderState.h>

namespace Liar
{
	enum CameraClearType
	{
		CLEARFLAG_NONE = 0,
		CLEARFLAG_SOLIDCOLOR,
		CLEARFLAG_SKY,
		CLEARFLAG_DEPTHONLY
	};

	class BaseCamera
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
		Liar::Vector4* m_clearColor;
		bool m_orthographic;
		bool m_transformChanged;
		Liar::CameraClearType m_clearFlag;

		virtual void CalculateProjectionMatrix();

	public:
		Liar::Number GetNearPlane() const { return m_nearPlane; };
		Liar::Number GetFarPlane() const { return m_farPlane; };
		Liar::Number GetFieldOfView() const { return m_fieldOfView; };
		Liar::Vector4* GetClearColor() { return m_clearColor; };
		bool GetOrthographic() const { return m_orthographic; };
		Liar::CameraClearType GetClearFlag() const { return m_clearFlag; };
		Liar::Transform3D& GetTransform3D() const { return *m_transform3D; };

		void SetClearFlag(Liar::CameraClearType type) { m_clearFlag = type; };

		void SetNearPlane(Liar::Number);
		void SetFarPlane(Liar::Number);
		void SetFieldOfView(Liar::Number);
		void SetOrthograpic(bool);
		void SetClearColor(const Liar::Vector4&);
		void SetClearColor(Liar::Number, Liar::Number, Liar::Number, Liar::Number alpha = 1.0f);

		void MoveForward(Liar::Number);
		void MoveHorizontal(Liar::Number);
		void MoveVertical(Liar::Number);

		virtual bool Render(Liar::RenderState& gl);

		virtual bool GetTransformChanged() const { return m_transformChanged || m_transform3D->GetTransformChanged(); };
		virtual Liar::Viewport& GetViewport() = 0;
		virtual Liar::Matrix4x4& GetProjectionMatrix() const = 0;
		virtual Liar::Matrix4x4& GetProjectionViewMatrix() const = 0;
	};
}