
#include <core/render/Renderer.h>

namespace Liar
{
	Renderer::Renderer():
		m_renderQueues(nullptr), m_numberRenderQueue(0),
		m_renderUnits(nullptr), m_numberRenderUnit(0), m_curIndexRenderUnit(0)
	{
	}


	Renderer::~Renderer()
	{
		for (int i = 0; i < m_numberRenderQueue; ++i)
		{
			if (m_renderQueues[i])
			{
				m_renderQueues[i]->Clear();
				delete m_renderQueues[i];
				m_renderQueues[i] = nullptr;
			}
		}

		if (m_renderQueues) free(m_renderQueues);
		m_numberRenderQueue = 0;

		for (Liar::Uint i = 0; i < m_numberRenderUnit; ++i)
		{
			if (m_renderUnits[i])
			{
				delete m_renderUnits[i];
				m_renderUnits[i] = nullptr;
			}
		}
		if (m_renderUnits) free(m_renderUnits);
		m_numberRenderUnit = 0;

	}

	Liar::RenderUnit* Renderer::AddRenderUnit(Liar::RenderUnit* unit, Liar::RenderQueueDefine type)
	{
		if (!unit) return unit;
		if (unit->material) type = unit->material->GetRenderQueue();
		if (type >= m_numberRenderQueue)
		{
			m_numberRenderQueue = type + 1;

			if (m_renderQueues) 
			{
				m_renderQueues = (Liar::RenderQueue**)realloc(m_renderQueues, sizeof(Liar::RenderQueue*)*m_numberRenderQueue);
			}
			else
			{
				m_renderQueues = (Liar::RenderQueue**)malloc(sizeof(Liar::RenderQueue*)*m_numberRenderQueue);
			}
			m_renderQueues[type] = new Liar::RenderQueue();
		}

		return m_renderQueues[type]->AddRenderUnit(unit);
	}

	Liar::RenderUnit* Renderer::PopRenderUnit()
	{
		if (m_curIndexRenderUnit > 0)
		{
			--m_curIndexRenderUnit;
			Liar::RenderUnit* render = m_renderUnits[m_curIndexRenderUnit];
			m_renderUnits[m_curIndexRenderUnit] = nullptr;
			return render;
		}
		else
		{
			++m_numberRenderUnit;
			if (m_renderUnits)
			{
				m_renderUnits = (Liar::RenderUnit**)realloc(m_renderUnits, sizeof(Liar::RenderUnit*)*m_numberRenderUnit);
			}
			else
			{
				m_renderUnits = (Liar::RenderUnit**)malloc(sizeof(Liar::RenderUnit*)*m_numberRenderUnit);
			}
			m_renderUnits[m_numberRenderUnit - 1] = nullptr;
			Liar::RenderUnit* render = new Liar::RenderUnit();
			return render;
		}
	}

	void Renderer::PushRenderUnit(Liar::RenderUnit* unit)
	{
		if (unit)
		{
			unit->Clear();
			m_renderUnits[m_curIndexRenderUnit++] = unit;
		}
	}

	void Renderer::Render(Liar::RenderState& state)
	{
		for (int i = 0; i < m_numberRenderQueue; ++i)
		{
			if (m_renderQueues[i])
			{
				m_renderQueues[i]->Render(state);
			}
		}
	}
}