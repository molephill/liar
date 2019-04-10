#pragma once

#include <core/display/EventDispatcher.h>
#include <core/events/MouseEvent.h>

namespace Liar
{
	class TypeEvent
	{
	public:
		TypeEvent();
		~TypeEvent();

	private:
		Liar::EventDispatcher** m_eventDispatchers;
		Liar::Int m_numberEventDispatchers;

	public:
		Liar::EventTypeDefine type;

	public:
		Liar::EventDispatcher* AddEvent(Liar::EventDispatcher*);
		Liar::EventDispatcher* RemoveEvent(Liar::EventDispatcher*);
		void DoAllEvents(const Liar::Event&);
	};

	class EventController
	{
	public:
		EventController();
		~EventController();

	private:
		Liar::TypeEvent** m_typeEvents;
		Liar::Int m_numberTypeEvents;
		Liar::MouseEvent* m_mouseEvent;

	public:
		Liar::EventDispatcher* AddEvent(Liar::EventTypeDefine, Liar::EventDispatcher*);
		Liar::EventDispatcher* RemoveEvent(Liar::EventTypeDefine, Liar::EventDispatcher*);
		void DoEvent(Liar::EventTypeDefine, const Liar::Event&);
		void SetMouseEvent(Liar::Number, Liar::Number, Liar::Boolen, Liar::Boolen, Liar::Boolen);
		void ScrollMouseEvent(Liar::Number, Liar::Number);

	private:
		Liar::TypeEvent* GetTypeEvent(Liar::EventTypeDefine);
	};
}
