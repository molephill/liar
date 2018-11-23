#pragma once

#include <core/render/BaseCamera.h>

namespace Liar
{
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