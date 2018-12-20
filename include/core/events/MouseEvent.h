#pragma once

#include "Event.h"

namespace Liar
{
	class MouseEvent:public Liar::Event
	{
	public:
		MouseEvent();
		~MouseEvent();

	private:
		Liar::DNumber m_mouseX;
		Liar::DNumber m_mouseY;
		bool m_leftDown;
		bool m_rightDown;
		bool m_midDown;

	public:

		virtual void Clear();
	};
}