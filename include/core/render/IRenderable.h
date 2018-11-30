#pragma once

#include <core/render/RenderState.h>
#include <core/render/StageContext.h>

namespace Liar
{
	class IRenderable
	{
	public:
		IRenderable() {};
		virtual ~IRenderable() {};

	public:
		virtual size_t GetNumberTriangles() = 0;
		virtual void BeforeRender(Liar::RenderState&) = 0;
		virtual bool Render(Liar::StageContext& gl, Liar::RenderState& state) = 0;
	};
}