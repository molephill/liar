#pragma once

#include <core/render/RenderUnit.h>
#include <core/render/RenderState.h>

namespace Liar
{
	class RenderQueue
	{
	public:
		RenderQueue();
		~RenderQueue();

	private:
		Liar::RenderUnit** m_renderUnits;
		Liar::Uint m_numberRenderUint;
		Liar::Uint m_curNumber;

	public:
		Liar::RenderUnit* AddRenderUnit(Liar::RenderUnit*);
		void Render(Liar::RenderState&);
		void Clear();
	};
}

