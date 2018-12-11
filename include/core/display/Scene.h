#pragma once

#include <core/display/Node.h>
#include <core/render/RenderQueue.h>

namespace Liar
{
	class Scene:public Liar::Node
	{
	public:
		Scene();
		virtual ~Scene();

	private:
		Liar::RenderQueue** m_renderQueues;
		Liar::Int m_numberRenderQueue;

	public:
		Liar::RenderUnit* AddRenderUnit(Liar::RenderUnit*, Liar::RenderQueueDefine type = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE);
	};
}