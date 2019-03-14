
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
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION:
			return new Liar::VertexPositionKey();
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
			return new Liar::VertexPositionColorKey();
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
			return new Liar::VertexPositionNormalKey();
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
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION:
			return new Liar::RawVertexBuffersPosition();
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
			return new Liar::RawVertexBuffersPositonColor();
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
			return new Liar::RawVertexBuffersPositonNormal();
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::RawVertexBuffersPositionNormalTexture(attr);
		default:
			return nullptr;
		}
	}
}