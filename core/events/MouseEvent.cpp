
#include <core/events/MouseEvent.h>

namespace Liar
{
	MouseEvent::MouseEvent():
		Liar::Event(),
		m_mouseX(Liar::ZERO), m_mouseY(Liar::ZERO),
		m_leftDown(false), m_rightDown(false), m_midDown(false)
	{
	}


	MouseEvent::~MouseEvent()
	{
	}

	Liar::EventTypeDefine MouseEvent::CheckMouseEventType(Liar::Number x, Liar::Number y, Liar::Boolen left, Liar::Boolen right, Liar::Boolen mid)
	{
		Liar::EventTypeDefine type = Liar::EventTypeDefine::EVENT_TYPE_NONE;
		if (left != m_leftDown)
		{
			type = left ? Liar::EventTypeDefine::EVENT_TYPE_MOUSE_DOWN : Liar::EventTypeDefine::EVENT_TYPE_MOUSE_UP;
		}
		else if (right != m_rightDown)
		{
			type = left ? Liar::EventTypeDefine::EVENT_TYPE_MOUSE_DOWN : Liar::EventTypeDefine::EVENT_TYPE_MOUSE_UP;
		}
		else if (mid != m_midDown)
		{
			type = left ? Liar::EventTypeDefine::EVENT_TYPE_MOUSE_DOWN : Liar::EventTypeDefine::EVENT_TYPE_MOUSE_UP;
		}
		else
		{
			if (m_mouseX != x || m_mouseY != y)
			{
				type = Liar::EventTypeDefine::EVENT_TYPE_MOUSE_MOVE;
			}
		}
		m_mouseX = x;
		m_mouseY = y;
		m_leftDown = left;
		m_rightDown = right;
		m_midDown = m_midDown;
		return type;
	}

	void MouseEvent::Clear()
	{
		m_mouseX = Liar::ZERO;
		m_mouseY = Liar::ZERO;
		m_leftDown = false;
		m_rightDown = false;
		m_midDown = false;
	}
}