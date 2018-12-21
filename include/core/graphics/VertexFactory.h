#pragma once

#include <core/graphics/RawVertexBuffersPositionNormalTexture.h>

namespace Liar
{
	class VertexFactory
	{
	public:
		VertexFactory();
		~VertexFactory();

	public:
		Liar::IVertexKey* GetVertexKey(Liar::GeometryVertexType attr);
		Liar::IRawVertexBuffers* GetRawVertexBuffers(Liar::GeometryVertexType attr);
	};
}