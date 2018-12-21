
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	VertexFactory::VertexFactory()
	{}

	VertexFactory::~VertexFactory()
	{
	}

	Liar::IVertexKey* VertexFactory::GetVertexKey(Liar::GeometryVertexType attr)
	{
		switch (attr)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::VertexPositionNormalTextureKey();
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