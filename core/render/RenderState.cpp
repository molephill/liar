

#include <core/render/RenderState.h>

namespace Liar
{
	RenderState::RenderState():
		clientWidth(0), clientHeight(0),
		camera(nullptr)
	{
	}

	RenderState::~RenderState()
	{
		camera = nullptr;
	}
}