#pragma once

#include <core/graphics/raws/RawVertexBuffersPositionNormalTexture.h>
#include <core/graphics/VertexBufferPositionNormalTexture.h>

namespace Liar
{
	class VertexFactory
	{
	public:
		VertexFactory();
		~VertexFactory();

	public:
		Liar::IVertexBuffer* GetVertexBuffer(Liar::GeometryVertexType attr);
		Liar::IRawVertexBuffers* GetRawVertexBuffers(Liar::GeometryVertexType attr);
	};
}