
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

	void TickRender::AddTickRender(Liar::ITickRender* render, void* args)
	{
		Liar::TickRender::TickNode* tickNode = new Liar::TickRender::TickNode();
		tickNode->node = render;
		tickNode->args = args;

		if (!m_current) m_current = tickNode;
		else m_tail->next = tickNode;

		m_tail = tickNode;
	}

	void TickRender::RemoveTickRender(Liar::ITickRender* render)
	{
		if (render)
		{
			if (m_current)
			{
				Liar::TickRender::TickNode* tmp = nullptr;
				if (m_current->node == render)
				{
					tmp = m_current->next;
					if (m_current == m_tail) m_tail = nullptr;
					delete m_current;
					m_current = tmp;
				}
				else
				{
					Liar::TickRender::TickNode* pre = m_current;
					Liar::TickRender::TickNode* cur = m_current;
					while (cur)
					{
						if (cur->node == render)
						{
							tmp = cur->next;
							if (cur == m_tail) m_tail = pre;
							delete cur;
							pre->next = tmp;
							return;
						}
						else
						{
							pre = cur;
							cur = cur->next;
						}
					}
				}
			}
		}
	}

	void TickRender::Loop()
	{
		if (m_current)
		{
			if (m_current->node->TickRender(m_current->args))
			{
				Liar::TickRender::TickNode* tmp = m_current->next;
				if (m_current == m_tail) m_tail = nullptr;
				delete m_current;
				m_current = tmp;
			}
		}
	}
}