#include <core/render/BaseCamera.h>

namespace Liar
{
	BaseCamera::BaseCamera(Liar::Number nearPlane, Liar::Number farPlane) :
		m_transform3D(new Liar::Transform3D()),
		m_nearPlane(nearPlane), m_farPlane(farPlane),
		m_orthographic(false), m_fieldOfView(60.f),
		m_orthographicVerticalSize(10.0f), m_transformChanged(true),
		m_clearColor(nullptr), m_clearFlag(Liar::CameraClearType::CLEARFLAG_SOLIDCOLOR)
	{
	}

	BaseCamera::~BaseCamera()
	{
		delete m_transform3D;
		m_transform3D = nullptr;
		if (m_clearColor)
		{
			delete m_clearColor;
			m_clearColor = nullptr;
		}
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

	void BaseCamera::SetClearColor(const Liar::Vector4& color)
	{
		SetClearColor(color.x, color.y, color.z, color.w);
	}

	void BaseCamera::SetClearColor(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number alpha)
	{
		if (!m_clearColor) m_clearColor = new Liar::Vector4();
		m_clearColor->Set(r, g, b, alpha);
	}

	void BaseCamera::CalculateProjectionMatrix()
	{
		m_transform3D->CalclateTransformation();
	}

	bool BaseCamera::Render(Liar::RenderState& state)
	{
		const Liar::BaseCamera& camera = *this;
		const Liar::Viewport& viewport = GetViewport();

		Liar::Number vpx = viewport.GetStartX();
		Liar::Number vpy = viewport.GetStartY();
		Liar::Number vpWidth = viewport.GetWidth();
		Liar::Number vpHeight = viewport.GetHeight();

		Liar::StageContext& gl = *state.stageContext;

		gl.Viewport(static_cast<GLsizei>(vpx), static_cast<GLsizei>(vpy), static_cast<GLint>(vpWidth), static_cast<GLint>(vpHeight));

		GLint flag = GL_DEPTH_BUFFER_BIT;
		switch (camera.GetClearFlag())
		{
		case CameraClearType::CLEARFLAG_SOLIDCOLOR:
		{
			Liar::Vector4* clearColor = GetClearColor();
			if (clearColor)
			{
				gl.Enable(GL_SCISSOR_TEST);
				gl.Scissor(static_cast<GLsizei>(vpx), static_cast<GLsizei>(vpy), static_cast<GLint>(vpWidth), static_cast<GLint>(vpHeight));
				gl.ClearColor(clearColor->x, clearColor->y, clearColor->z, clearColor->w);
				flag |= GL_COLOR_BUFFER_BIT;
			}
			gl.Clear(flag);
			if (clearColor)
			{
				gl.Disable(GL_SCISSOR_TEST);
			}
			break;
		}
		default:
			break;
		}

		CalculateProjectionMatrix();

		return true;
	}

	// 前后移动 
	void BaseCamera::MoveForward(Liar::Number distance)
	{
		Liar::Vector3& tmp = Liar::MathUtils3D::TEMPVector30;
		tmp[0] = tmp[1] = 0.0f;
		tmp[2] = distance;
		m_transform3D->Translate(tmp);
	}

	// 水平移动 
	void BaseCamera::MoveHorizontal(Liar::Number distance)
	{
		Liar::Vector3& tmp = Liar::MathUtils3D::TEMPVector30;
		tmp[1] = tmp[2] = 0.0f;
		tmp[0] = distance;
		m_transform3D->Translate(tmp);
	}

	// 垂直移动
	void BaseCamera::MoveVertical(Liar::Number distance)
	{
		Liar::Vector3& tmp = Liar::MathUtils3D::TEMPVector30;
		tmp[0] = tmp[2] = 0.0f;
		tmp[1] = distance;
		m_transform3D->Translate(tmp);
	}
}
