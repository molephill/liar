#pragma once

#include <core/events/EventType.h>
#include <core/events/Event.h>

namespace Liar
{
	/*class EventTypeFun
	{
	public:
		EventTypeFun();
		~EventTypeFun();

	public:
		Liar::EventTypeDefine type;

	private:
		Liar::EventFun** m_funs;
		Liar::Int m_numberFuns;

	private:
		Liar::Boolen HasFun(Liar::EventFun*);

	public:
		void AddFun(Liar::EventFun*);
	};*/

	class EventDispatcher
	{
	public:
		EventDispatcher();
		virtual ~EventDispatcher();

	protected:
		int m_eventDefine;
		/*Liar::EventTypeFun** m_eventFuns;
		Liar::Int m_numberEventFuns;*/

	public:
		void AddEvent(Liar::EventTypeDefine);
		void RemoveEvent(Liar::EventTypeDefine);
		virtual void DoEvent(Liar::EventTypeDefine, const Liar::Event&);
		//void AddEvent(Liar::EventTypeDefine, Liar::EventFun*);

	protected:
		bool HasType(Liar::EventTypeDefine);
		//Liar::EventTypeFun* HasEventFun(Liar::EventTypeDefine);
	};
}