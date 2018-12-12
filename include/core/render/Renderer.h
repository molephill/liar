#pragma once

#include <core/render/RenderQueue.h>
#include <core/render/RenderState.h>

namespace Liar
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

	private:
		Liar::RenderQueue** m_renderQueues;
		Liar::Int m_numberRenderQueue;

		Liar::RenderUnit** m_renderUnits;
		Liar::Uint m_numberRenderUnit;
		Liar::Uint m_curIndexRenderUnit;

	public:
		Liar::RenderUnit* PopRenderUnit();
		void PushRenderUnit(Liar::RenderUnit*);
		Liar::RenderUnit* AddRenderUnit(Liar::RenderUnit*, Liar::RenderQueueDefine type = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE);
		void Render(Liar::RenderState&);
	};
}

