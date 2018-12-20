
#include <core/events/MouseEvent.h>

namespace Liar
{
	MouseEvent::MouseEvent():
		Liar::Event(),
		m_mouseX(0.0), m_mouseY(0.0),
		m_leftDown(false), m_rightDown(false), m_midDown(false)
	{
	}


	MouseEvent::~MouseEvent()
	{
	}

	void MouseEvent::Clear()
	{
		m_mouseX = 0.0;
		m_mouseY = 0.0;
		m_leftDown = false;
		m_rightDown = false;
		m_midDown = false;
	}
}