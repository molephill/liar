#pragma once

#include "Event.h"
#include "EventType.h"

namespace Liar
{
	class MouseEvent:public Liar::Event
	{
	public:
		MouseEvent();
		~MouseEvent();

	private:
		Liar::Number m_mouseX;
		Liar::Number m_mouseY;
		bool m_leftDown;
		bool m_rightDown;
		bool m_midDown;

	public:
		Liar::EventTypeDefine CheckMouseEventType(Liar::Number, Liar::Number, Liar::Boolen, Liar::Boolen, Liar::Boolen);
		virtual void Clear();
	};
}