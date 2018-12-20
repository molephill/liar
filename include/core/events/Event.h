#pragma once

#include "EventType.h"
#include <LiarType.h>

namespace Liar
{
	class Event
	{
	public:
		Event(Liar::EventTypeDefine type = Liar::EventTypeDefine::EVENT_TYPE_NONE);
		virtual ~Event();

	protected:
		Liar::EventTypeDefine m_type;

	public:
		Liar::EventTypeDefine GetType() const { return m_type; };
		void SetType(Liar::EventTypeDefine type) { m_type = type; };
		virtual void Clear() {};
	};
}

