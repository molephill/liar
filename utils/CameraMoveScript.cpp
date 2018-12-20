
#include <utils/CameraMoveScript.h>

namespace Liar
{
	CameraMoveScript::CameraMoveScript() :
		m_yawPitchRoll(new Liar::Vector3()),
		m_lastMouseX(0.0), m_lastMouseY(0.0),
		m_camera(nullptr), m_isMouseDown(false)
	{
	}


	CameraMoveScript::~CameraMoveScript()
	{
		delete m_yawPitchRoll;
		m_yawPitchRoll = nullptr;
		m_camera = nullptr;
	}

	void CameraMoveScript::SetCamera(Liar::BaseCamera* camera)
	{
		m_camera = camera;
	}

	void CameraMoveScript::MouseEvent(Liar::DNumber x, Liar::DNumber y, bool isMouseDown)
	{
		if (!m_camera)return;
		if (isMouseDown)
		{
			if (m_isMouseDown)
			{
				Liar::DNumber offsetX = x - m_lastMouseX;
				Liar::DNumber offsetY = y - m_lastMouseY;
				Liar::Number rotaionSpeed = 0.2f;
				m_yawPitchRoll->x = m_yawPitchRoll->x - offsetX * rotaionSpeed;
				m_yawPitchRoll->y = m_yawPitchRoll->y - offsetY * rotaionSpeed;
				UpdateRotation();
			}
			else
			{
				m_camera->GetTransform3D().GetRotation().GetYawPitchRoll(*m_yawPitchRoll);
			}
			m_lastMouseX = x;
			m_lastMouseY = y;
		}
		m_isMouseDown = isMouseDown;
	}

	void CameraMoveScript::UpdateRotation()
	{
		if (m_yawPitchRoll->y < 1.50f)
		{
			m_camera->GetTransform3D().Rotate(*m_yawPitchRoll);
		}
	}
}
