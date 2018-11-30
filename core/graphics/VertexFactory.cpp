
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	VertexFactory::VertexFactory()
	{}

	VertexFactory::~VertexFactory()
	{
	}

	Liar::IVertexBuffer* VertexFactory::GetVertexBuffer(Liar::GeometryVertexType attr)
	{
		switch (attr)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::VertexBufferPositionNormalTexture();
		default:
			return nullptr;
		}
	}

	Liar::IRawVertexBuffers* VertexFactory::GetRawVertexBuffers(Liar::GeometryVertexType attr)
	{
		switch (attr)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::RawVertexBuffersPositionNormalTexture();
		default:
			return nullptr;
		}
	}
}