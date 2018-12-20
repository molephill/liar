#pragma once

#include <core/events/EventType.h>

namespace Liar
{
	class EventDispatcher
	{
	public:
		EventDispatcher();
		virtual ~EventDispatcher();

	protected:
		int m_eventDefine;

	public:
		void AddEvent(Liar::EventTypeDefine);
		void RemoveEvent(Liar::EventTypeDefine);
		void DoEvent(Liar::EventTypeDefine);

	protected:
		bool HasType(Liar::EventTypeDefine);
	};
}