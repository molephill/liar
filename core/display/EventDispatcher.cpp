
#include <core/display/EventDispatcher.h>
#include <Liar3D.h>

namespace Liar
{
	EventDispatcher::EventDispatcher() :
		m_eventDefine(0)
	{}

	EventDispatcher::~EventDispatcher()
	{
		if (m_eventDefine > 0)
		{
			for (int i = 0; i < Liar::EventTypeDefine::EVENT_TYPE_LAST; ++i)
			{
				Liar::EventTypeDefine type = static_cast<Liar::EventTypeDefine>(i);
				if (HasType(type)) Liar::Liar3D::events->RemoveEvent(type, this);
			}
		}
	}

	void EventDispatcher::AddEvent(Liar::EventTypeDefine type)
	{
		if (type > 0 && !HasType(type))
		{
			m_eventDefine |= type;
			Liar::Liar3D::events->AddEvent(type, this);
		}
	}

	void EventDispatcher::RemoveEvent(Liar::EventTypeDefine type)
	{
		if (type > 0 && HasType(type))
		{
			m_eventDefine &= ~type;
			Liar::Liar3D::events->RemoveEvent(type, this);
		}
	}

	void EventDispatcher::DoEvent(Liar::EventTypeDefine)
	{

	}

	bool EventDispatcher::HasType(Liar::EventTypeDefine type)
	{
		return (m_eventDefine & type) == type;
	}
}