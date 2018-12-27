
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

		for (Liar::Int i = 0; i < m_numberNetGeometries; ++i)
		{
			m_netGeometries[i] = nullptr;
		}
		if (m_netGeometries) free(m_netGeometries);
		m_netGeometries = nullptr;
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

	Liar::Geometry* GeometryFactory::GetGeometry(const char* url)
	{
		Liar::NetGeometry* tmp = nullptr;
		for (Liar::Int i = 0; i < m_numberNetGeometries; ++i)
		{
			tmp = m_netGeometries[i];
			if ((*tmp) == url)
			{
				tmp->AddRefrence();
				return tmp;
			}
		}

		++m_numberNetGeometries;
		size_t len = sizeof(Liar::NetGeometry*)*m_numberNetGeometries;
		if (m_netGeometries) m_netGeometries = (Liar::NetGeometry**)realloc(m_netGeometries, len);
		else m_netGeometries = (Liar::NetGeometry**)malloc(len);

		tmp = new Liar::NetGeometry();
		tmp->AddRefrence();
		tmp->SetURL(url);
		m_netGeometries[m_numberNetGeometries - 1] = tmp;
		return tmp;
	}
}