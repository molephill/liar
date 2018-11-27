#pragma once

#include <LiarType.h>

namespace Liar
{
	class BaseCamera;

	class RenderState
	{
	public:
		RenderState();
		~RenderState();

	public:
		Liar::Uint clientWidth;
		Liar::Uint clientHeight;

		Liar::BaseCamera* camera;
	};
}