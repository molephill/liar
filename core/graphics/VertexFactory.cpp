
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	VertexFactory::VertexFactory()
	{}

	VertexFactory::~VertexFactory()
	{
	}

	Liar::IVertexBuffer* VertexFactory::GetVertexBuffer(Liar::MeshVertexType attr)
	{
		switch (attr)
		{
		case Liar::MeshVertexType::MESH_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::VertexBufferPositionNormalTexture();
		default:
			return nullptr;
		}
	}

	Liar::IRawVertexBuffers* VertexFactory::GetRawVertexBuffers(Liar::MeshVertexType attr)
	{
		switch (attr)
		{
		case Liar::MeshVertexType::MESH_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::RawVertexBuffersPositionNormalTexture();
		default:
			return nullptr;
		}
	}
}