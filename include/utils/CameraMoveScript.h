#pragma once

#include <math/Vector3.h>
#include <core/render/BaseCamera.h>
#include <core/display/EventDispatcher.h>

namespace Liar
{
	class CameraMoveScript:public Liar::EventDispatcher
	{
	public:
		CameraMoveScript();
		~CameraMoveScript();

	private:
		Liar::Vector3* m_yawPitchRoll;
		Liar::Number m_lastMouseX;
		Liar::Number m_lastMouseY;
		Liar::BaseCamera* m_camera;
		Liar::Number m_rotaionSpeed;
		bool m_isMouseDown;

	public:
		void SetCamera(Liar::BaseCamera*);
		virtual void DoEvent(Liar::EventTypeDefine, const Liar::Event&);

	private:
		void UpdateCamera();
		void UpdateRotation();
	};
}
