#pragma once

#include <core/render/RenderUnit.h>

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
		void Clear();
	};
}

