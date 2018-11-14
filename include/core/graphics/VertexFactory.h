#pragma once

#include <core/graphics/VertexType.h>

#include <core/graphics/raws/RawVertexBuffersPositionNormalTexture.h>
#include <core/graphics/VertexBufferPositionNormalTexture.h>

namespace Liar
{
	class VertexFactory
	{
	public:
		VertexFactory() {};
		~VertexFactory() {};

	public:
		IVertexBuffer* GetVertexBuffer(Liar::MeshVertexType attr)
		{
			switch (attr)
			{
			case Liar::MeshVertexType::POSITION_NORMAL_COLOR_TEXTURE:
				return (Liar::VertexBufferPositionNormalTexture*)malloc(sizeof(Liar::VertexBufferPositionNormalTexture));
			default:
				return nullptr;
			}
		};

		IRawVertexBuffers* GetRawVertexBuffers(Liar::MeshVertexType attr)
		{
			switch (attr)
			{
			case Liar::MeshVertexType::POSITION_NORMAL_COLOR_TEXTURE:
				return (Liar::RawVertexBuffersPositionNormalTexture*)malloc(sizeof(Liar::RawVertexBuffersPositionNormalTexture));
			default:
				return nullptr;
			}
		};
	};
}