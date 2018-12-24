
#include <core/models/GeometryFactory.h>
#include <core/models/geometries/BoxGeometry.h>

namespace Liar
{
	GeometryFactory::GeometryFactory():
		m_vertexFactory(new Liar::VertexFactory())
	{
	}


	GeometryFactory::~GeometryFactory()
	{
		delete m_vertexFactory;
		m_vertexFactory = nullptr;
	}

	Liar::Int GeometryFactory::GetVertexNumberFloat(Liar::GeometryVertexType type)
	{
		Liar::Int num = 0;
		switch (type)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION:
			// 3
			num = 3;
			break;
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
			// 3 + 3
			num = 6;
			break;
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR:
			// 3 + 3 + 4
			num = 10;
			break;
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			// 3 + 3 + 2
			num = 8;
			break;
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE:
			// 3 + 3 + 4 + 2
			num = 12;
			break;
		default:
			num = 0;
		}
		return num;
	}

	Liar::Geometry* GeometryFactory::GetGeometry(Liar::GeometryType type)
	{
		switch (type)
		{
		case Liar::GeometryType::GEOMETRY_TYPE_BOX:
		{
			Liar::BoxGeometry* box = new Liar::BoxGeometry();
			box->AddRefrence();
			box->SetGeometryVertexType(Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE);
			return box;
		}
		default:
			return nullptr;
		}
	}
}