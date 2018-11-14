#pragma once

#include <events/EventDispatcher.h>

namespace Liar
{
	class BaseRender :public Liar::EventDispatcher
	{
	public:
		BaseRender() :
			Liar::EventDispatcher()
		{};
		virtual ~BaseRender()
		{};
	};
}