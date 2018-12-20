#pragma once

#include <math/Vector3.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	class CameraMoveScript
	{
	public:
		CameraMoveScript();
		~CameraMoveScript();

	private:
		Liar::Vector3* m_yawPitchRoll;
		Liar::DNumber m_lastMouseX;
		Liar::DNumber m_lastMouseY;
		Liar::BaseCamera* m_camera;
		bool m_isMouseDown;

	public:
		void MouseEvent(Liar::DNumber, Liar::DNumber, bool);
		void SetCamera(Liar::BaseCamera*);

	private:
		void UpdateRotation();
	};
}
