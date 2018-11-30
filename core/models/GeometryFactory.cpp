
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