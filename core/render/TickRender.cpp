
#include <core/render/TickRender.h>

namespace Liar
{
	TickRender::TickRender():
		m_current(nullptr), m_tail(nullptr)
	{
	}


	TickRender::~TickRender()
	{
		Liar::TickRender::TickNode* current = m_current;
		Liar::TickRender::TickNode* tmp = nullptr;
		while (current)
		{
			tmp = current->next;
			delete current;
			current = tmp;
		}
		m_current = nullptr;
		m_tail = nullptr;
	}

	void TickRender::AddTickRender(Liar::ITickRender* render)
	{
		if (!m_current)
		{
			m_current = new Liar::TickRender::TickNode();
			m_current->node = render;
			m_tail = m_current;
		}
		else
		{
			m_tail->next = new Liar::TickRender::TickNode();
			m_tail->next->node = render;
			m_tail->next->next = m_tail;
		}
	}

	void TickRender::Loop()
	{
		if (m_current)
		{
			if (m_current->node->TickRender())
			{
				Liar::TickRender::TickNode* tmp = m_current->next;
				delete m_current;
				m_current = tmp;
			}
		}
	}
}