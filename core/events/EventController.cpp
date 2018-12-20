
#include <core/events/EventController.h>

namespace Liar
{
	TypeEvent::TypeEvent(): 
	m_eventDispatchers(nullptr), m_numberEventDispatchers(0),
		type(Liar::EventTypeDefine::EVENT_TYPE_NONE)
	{}

	TypeEvent::~TypeEvent()
	{
		if (m_eventDispatchers)
		{
			for (int i = 0; i < m_numberEventDispatchers; ++i)
			{
				m_eventDispatchers[i] = nullptr;
			}
			free(m_eventDispatchers);
			m_eventDispatchers = nullptr;
		}
	}

	Liar::EventDispatcher* TypeEvent::AddEvent(Liar::EventDispatcher* dispatcher)
	{
		if (dispatcher)
		{
			Liar::Int findIndex = -1;
			for (int i = 0; i < m_numberEventDispatchers; ++i)
			{
				if (m_eventDispatchers[i] == nullptr)
				{
					findIndex = i;
					break;
				}
			}

			if (findIndex < 0)
			{
				findIndex = m_numberEventDispatchers++;
				if (m_eventDispatchers)
				{
					m_eventDispatchers = (Liar::EventDispatcher**)realloc(m_eventDispatchers, sizeof(Liar::EventDispatcher*)*m_numberEventDispatchers);
				}
				else
				{
					m_eventDispatchers = (Liar::EventDispatcher**)malloc(sizeof(Liar::EventDispatcher*)*m_numberEventDispatchers);
				}
			}
			m_eventDispatchers[findIndex] = dispatcher;
		}
		return dispatcher;
	}

	Liar::EventDispatcher* TypeEvent::RemoveEvent(Liar::EventDispatcher* dispatcher)
	{
		if (dispatcher)
		{
			for (int i = 0; i < m_numberEventDispatchers; ++i)
			{
				if (m_eventDispatchers[i] == dispatcher)
				{
					m_eventDispatchers[i] = nullptr;
					return dispatcher;
				}
			}
		}
		return dispatcher;
	}

	void TypeEvent::DoAllEvents()
	{
		for (int i = 0; i < m_numberEventDispatchers; ++i)
		{
			if (m_eventDispatchers[i])
			{
				m_eventDispatchers[i]->DoEvent(type);
			}
		}
	}

	// ================================== 事件总控制 =====================
	EventController::EventController():
		m_typeEvents(nullptr), m_numberTypeEvents(0)
	{
	}

	EventController::~EventController()
	{
		if (m_typeEvents)
		{
			for (int i = 0; i < m_numberTypeEvents; ++i)
			{
				delete m_typeEvents[i];
				m_typeEvents[i] = nullptr;
			}
			free(m_typeEvents);
			m_typeEvents = nullptr;
		}
	}

	// ================= 增加事件 ==============
	Liar::EventDispatcher* EventController::AddEvent(Liar::EventTypeDefine type, Liar::EventDispatcher* dispatcher)
	{
		if (dispatcher)
		{
			Liar::TypeEvent* typeEvent = GetTypeEvent(type);
			if (!typeEvent)
			{
				typeEvent = new TypeEvent();
				typeEvent->type = type;

				++m_numberTypeEvents;
				if (m_typeEvents)
				{
					m_typeEvents = (Liar::TypeEvent**)realloc(m_typeEvents, sizeof(Liar::TypeEvent*)*m_numberTypeEvents);
				}
				else
				{
					m_typeEvents = (Liar::TypeEvent**)malloc(sizeof(Liar::TypeEvent*)*m_numberTypeEvents);
				}
				m_typeEvents[m_numberTypeEvents - 1] = typeEvent;
			}
			return typeEvent->AddEvent(dispatcher);
		}
		return dispatcher;
	}

	Liar::EventDispatcher* EventController::RemoveEvent(Liar::EventTypeDefine type, Liar::EventDispatcher* dispatcher)
	{
		if (dispatcher)
		{
			Liar::TypeEvent* typeEvent = GetTypeEvent(type);
			if (typeEvent) return typeEvent->RemoveEvent(dispatcher);
		}
		return dispatcher;
	}

	void EventController::DoEvent(Liar::EventTypeDefine type)
	{
		Liar::TypeEvent* typeEvent = GetTypeEvent(type);
		if (typeEvent) typeEvent->DoAllEvents();
	}

	Liar::TypeEvent* EventController::GetTypeEvent(Liar::EventTypeDefine type)
	{
		if (m_typeEvents)
		{
			for (int i = 0; i < m_numberTypeEvents; ++i)
			{
				if (type == m_typeEvents[i]->type)
				{
					return m_typeEvents[i];
				}
			}
		}
		return nullptr;
	}
}