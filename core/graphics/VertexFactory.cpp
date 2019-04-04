
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	VertexFactory::VertexFactory()
	{}

	VertexFactory::~VertexFactory()
	{
	}

	Liar::IRawVertexBuffers* VertexFactory::GetRawVertexBuffers(Liar::GeometryVertexType attr)
	{
		switch (attr)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION:
			return new Liar::RawVertexBuffersPosition(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
			return new Liar::RawVertexBuffersPositionColor(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
			return new Liar::RawVertexBuffersPositionNormal(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::RawVertexBuffersPositionNormalTexture(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE_SKIN:
			return new Liar::RawVertexBuffersPositionNormalTextureSkin(attr);
		default:
			return nullptr;
		}
	}

	Liar::ISubVertexBuffers* VertexFactory::GetSubVertexBuffers(Liar::VertexFormatType type)
	{
		switch (type)
		{
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2:
			return new Liar::SubVector2VertexBuffer();
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3:
			return new Liar::SubVector3VertexBuffer();
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4:
			return new Liar::SubVector4VertexBuffer();
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION:
			return new Liar::SubQuatVertexBuffer();
		default:
			return nullptr;
		}
	}
}