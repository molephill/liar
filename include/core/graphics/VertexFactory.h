#pragma once

#include <core/graphics/RawVertexBuffersPositionNormalTextureSkin.h>
#include <core/graphics/RawVertexBuffersPositionColor.h>

namespace Liar
{
	class VertexFactory
	{
	public:
		VertexFactory();
		~VertexFactory();

	public:
		Liar::IRawVertexBuffers* GetRawVertexBuffers(Liar::GeometryVertexType attr);
	};
}