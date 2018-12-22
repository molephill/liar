
#include <utils/CameraMoveScript.h>
#include <Liar3D.h>

namespace Liar
{
	CameraMoveScript::CameraMoveScript() :
		Liar::EventDispatcher(),
		m_yawPitchRoll(new Liar::Vector3()),
		m_lastMouseX(0.0), m_lastMouseY(0.0),
		m_camera(nullptr), m_isMouseDown(false),
		m_rotaionSpeed(0.0006f)
	{
		AddEvent(Liar::EventTypeDefine::EVENT_TYPE_MOUSE_DOWN);
		AddEvent(Liar::EventTypeDefine::EVENT_TYPE_MOUSE_UP);
	}

	CameraMoveScript::~CameraMoveScript()
	{
		delete m_yawPitchRoll;
		m_yawPitchRoll = nullptr;
		m_camera = nullptr;
	}

	void CameraMoveScript::DoEvent(Liar::EventTypeDefine type, const Liar::Event& e)
	{
		switch (type)
		{
		case Liar::EventTypeDefine::EVENT_TYPE_MOUSE_DOWN:
		{
			m_camera->GetTransform3D().GetRotation().GetYawPitchRoll(*m_yawPitchRoll);
			AddEvent(Liar::EventTypeDefine::EVENT_TYPE_MOUSE_MOVE);
			m_isMouseDown = true;
			m_lastMouseX = Liar::Liar3D::stage->mouseX;
			m_lastMouseY = Liar::Liar3D::stage->mouseY;
			break;
		}
		case Liar::EventTypeDefine::EVENT_TYPE_MOUSE_UP:
			m_isMouseDown = false;
			RemoveEvent(Liar::EventTypeDefine::EVENT_TYPE_MOUSE_MOVE);
			break;
		case Liar::EventTypeDefine::EVENT_TYPE_MOUSE_MOVE:
			UpdateCamera();
			break;
		default:
			break;
		}
	}

	void CameraMoveScript::SetCamera(Liar::BaseCamera* camera)
	{
		m_camera = camera;
	}

	void CameraMoveScript::UpdateCamera()
	{
		if (!m_camera)return;
		Liar::Number x = Liar::Liar3D::stage->mouseX;
		Liar::Number y = Liar::Liar3D::stage->mouseY;
		if (m_isMouseDown)
		{
			Liar::Number offsetX = x - m_lastMouseX;
			Liar::Number offsetY = y - m_lastMouseY;
			Liar::Int elapsedTime = Liar::Liar3D::renderState->elapsedTime;
			m_yawPitchRoll->x = m_yawPitchRoll->x - offsetX * m_rotaionSpeed * elapsedTime;
			m_yawPitchRoll->y = m_yawPitchRoll->y - offsetY * m_rotaionSpeed * elapsedTime;
			UpdateRotation();
		}
		m_lastMouseX = x;
		m_lastMouseY = y;
	}

	void CameraMoveScript::UpdateRotation()
	{
		if (m_yawPitchRoll->y < 1.50f)
		{
			m_camera->GetTransform3D().SetRotation(*m_yawPitchRoll);
		}
	}
}
