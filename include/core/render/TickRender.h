#pragma once

#include <LiarType.h>

namespace Liar
{
	class ITickRender
	{
	public:
		virtual bool TickRender(Liar::Int = Liar::TICK_INTERVAL) = 0;
	};

	class TickRender
	{
	private:
		class TickNode;

	public:
		TickRender();
		~TickRender();

	private:
		Liar::TickRender::TickNode* m_current;
		Liar::TickRender::TickNode* m_tail;

	public:
		void AddTickRender(Liar::ITickRender*);
		void Loop();
	};

	class Liar::TickRender::TickNode
	{
	public:
		TickNode() :node(nullptr), next(nullptr) {};
		~TickNode()
		{
			node = nullptr;
			next = nullptr;
		}

	public:
		Liar::ITickRender* node;
		Liar::TickRender::TickNode* next;
	};
}