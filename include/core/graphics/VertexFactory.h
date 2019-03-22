#pragma once

#include "RawVertexBuffersPositionNormalTexture.h"
#include "RawVertexBuffersPositonColor.h"

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