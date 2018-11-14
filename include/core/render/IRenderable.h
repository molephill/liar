#pragma once

#include <core/render/RenderState.h>

namespace Liar
{
	class IRenderable
	{
	public:
		IRenderable() {};
		virtual ~IRenderable() {};

	public:
		virtual size_t GetNumberTriangles() const = 0;
		virtual void BeforeRender(Liar::RenderState&) = 0;
		virtual void Render(Liar::RenderState&) = 0;
	};
}