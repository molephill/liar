
#include <core/render/RenderQueue.h>
#include <Liar3D.h>

namespace Liar
{
	RenderQueue::RenderQueue():
		m_renderUnits(nullptr),
		m_numberRenderUint(0), m_curNumber(0)
	{
	}


	RenderQueue::~RenderQueue()
	{
		Clear();
		if (m_renderUnits) free(m_renderUnits);
	}

	Liar::RenderUnit* RenderQueue::AddRenderUnit(Liar::RenderUnit* unit)
	{
		if (!unit) return unit;
		if (m_renderUnits)
		{
			if (m_curNumber >= m_numberRenderUint)
			{
				m_numberRenderUint = m_curNumber + 1;
				m_renderUnits = (Liar::RenderUnit**)realloc(m_renderUnits, sizeof(Liar::RenderUnit*)*m_numberRenderUint);
			}
		}
		else
		{
			++m_numberRenderUint;
			m_renderUnits = (Liar::RenderUnit**)malloc(sizeof(Liar::RenderUnit*)*m_numberRenderUint);
		}
		m_renderUnits[m_curNumber++] = unit;
		return unit;
	}

	void RenderQueue::Render(Liar::RenderState& state, Liar::Geometry* preGeometry, Liar::BaseMaterial* preMaterial, Liar::ShaderCompile* preShaderCompile)
	{
		for (size_t i = 0; i < m_curNumber; ++i)
		{
			m_renderUnits[i]->Render(state, preGeometry, preMaterial, preShaderCompile);
			Liar::Liar3D::rendering->PushRenderUnit(m_renderUnits[i]);
			m_renderUnits[i] = nullptr;
		}
		m_curNumber = 0;
	}

	void RenderQueue::Clear()
	{
		for (size_t i = 0; i < m_numberRenderUint; ++i)
		{
			if (m_renderUnits[i]) Liar::Liar3D::rendering->PushRenderUnit(m_renderUnits[i]);
			m_renderUnits[i] = nullptr;
		}
		m_curNumber = 0;
	}
}