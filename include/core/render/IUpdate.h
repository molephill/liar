#pragma once

#include "RenderState.h"

namespace Liar
{
	class IUpdate
	{
	public:
		virtual void Update(Liar::RenderState*) = 0;
	};
}