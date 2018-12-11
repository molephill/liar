
#include <core/render/RenderUnit.h>

namespace Liar
{
	RenderUnit::RenderUnit():
		transform(nullptr), material(nullptr),
		geometry(nullptr)
	{
	}


	RenderUnit::~RenderUnit()
	{
		Clear();
	}

	void RenderUnit::Clear()
	{
		transform = nullptr;
		material = nullptr;
		geometry = nullptr;
	}
}