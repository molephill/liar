#pragma once

#include <core/display/EventDispatcher.h>

namespace Liar
{
	class BaseRender :public Liar::EventDispatcher
	{
	public:
		BaseRender();
		virtual ~BaseRender();
	};
}