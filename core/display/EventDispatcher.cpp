
#include <core/display/EventDispatcher.h>
#include <Liar3D.h>

namespace Liar
{
	/*EventTypeFun::EventTypeFun():
		m_funs(nullptr), m_numberFuns(0)
	{}

	EventTypeFun::~EventTypeFun()
	{
		if (m_funs) free(m_funs);
		m_funs = nullptr;
	}

	void EventTypeFun::AddFun(Liar::EventFun* fun)
	{
		if (!HasFun(fun))
		{
			++m_numberFuns;
			if (m_funs) m_funs = (Liar::EventFun**)realloc(m_funs, sizeof(Liar::EventFun*)*m_numberFuns);
			else m_funs = (Liar::EventFun**)malloc(sizeof(Liar::EventFun*)*m_numberFuns);
			m_funs[m_numberFuns - 1] = fun;
		}
	}

	Liar::Boolen EventTypeFun::HasFun(Liar::EventFun* fun)
	{
		for (int i = 0; i < m_numberFuns; ++i)
		{
			if (m_funs[i] == fun) return true;
		}
		return false;
	}*/

	// =================================================================== 

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

	void EventDispatcher::DoEvent(Liar::EventTypeDefine, const Liar::Event&)
	{

	}

	bool EventDispatcher::HasType(Liar::EventTypeDefine type)
	{
		return (m_eventDefine & type) == type;
	}

	/*void EventDispatcher::AddEvent(Liar::EventTypeDefine type, Liar::EventFun* fun)
	{
		Liar::EventTypeFun* typeFun = HasEventFun(type);
		if (!fun)
		{
			typeFun = new EventTypeFun();
			typeFun->type = type;

			++m_numberEventFuns;
			if (m_eventFuns) m_eventFuns = (Liar::EventTypeFun**)realloc(m_eventFuns, sizeof(Liar::EventTypeFun*)*m_numberEventFuns);
			else m_eventFuns = (Liar::EventTypeFun**)malloc(sizeof(Liar::EventTypeFun*)*m_numberEventFuns);
			m_eventFuns[m_numberEventFuns - 1] = typeFun;
		}
		typeFun->AddFun(fun);
	}

	Liar::EventTypeFun* EventDispatcher::HasEventFun(Liar::EventTypeDefine type)
	{
		for (int i = 0; i < m_numberEventFuns; ++i)
		{
			if (m_eventFuns[i]->type == type) return m_eventFuns[i];
		}
		return nullptr;
	}*/
}