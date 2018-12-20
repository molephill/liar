#pragma once

#include <core/display/EventDispatcher.h>
#include <LiarType.h>

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
		void DoAllEvents();
	};

	class EventController
	{
	public:
		EventController();
		~EventController();

	private:
		Liar::TypeEvent** m_typeEvents;
		Liar::Int m_numberTypeEvents;

	public:
		Liar::EventDispatcher* AddEvent(Liar::EventTypeDefine, Liar::EventDispatcher*);
		Liar::EventDispatcher* RemoveEvent(Liar::EventTypeDefine, Liar::EventDispatcher*);
		void DoEvent(Liar::EventTypeDefine);

	private:
		Liar::TypeEvent* GetTypeEvent(Liar::EventTypeDefine);
	};
}
