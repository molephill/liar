#include <core/display/Scene.h>

namespace Liar
{
	Scene::Scene():
		Liar::Node(),
		m_renderQueues(nullptr), m_numberRenderQueue(0)
	{
	}

	Scene::~Scene()
	{
		Destroy();
	}

	Liar::RenderUnit* Scene::AddRenderUnit(Liar::RenderUnit* unit, Liar::RenderQueueDefine type)
	{
		if (!unit) return unit;
		if (unit->material) type = unit->material->GetRenderQueue();
		if (type >= m_numberRenderQueue)
		{
			m_numberRenderQueue = type + 1;
			
			if (m_renderQueues) m_renderQueues = (Liar::RenderQueue**)realloc(m_renderQueues, sizeof(Liar::RenderQueue*)*m_numberRenderQueue);
			else m_renderQueues = (Liar::RenderQueue**)malloc(sizeof(Liar::RenderQueue*)*m_numberRenderQueue);
		}

		return m_renderQueues[type]->AddRenderUnit(unit);
	}
	
}
