#pragma once

#include <core/GLContext.h>
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	class GL
	{
	public:
		static Liar::GLContext mainContext;
		static Liar::VertexFactory vertexFactory;
	};

	Liar::GLContext GL::mainContext = Liar::GLContext();
	Liar::VertexFactory GL::vertexFactory = Liar::VertexFactory();
}