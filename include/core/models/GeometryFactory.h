#pragma once

#include <core/models/geometries/Geometry.h>
#include <core/graphics/VertexFactory.h>
#include <core/models/geometries/NetGeometry.h>

namespace Liar
{

	class GeometryFactory
	{
	public:
		GeometryFactory();
		~GeometryFactory();

	private:
		Liar::VertexFactory* m_vertexFactory;

		Liar::NetGeometry** m_netGeometries;
		Liar::Int m_numberNetGeometries;

	public:
		Liar::VertexFactory& GetVertexFactory() { return *m_vertexFactory; };
		Liar::Geometry* GetGeometry(Liar::GeometryType);
		Liar::Geometry* GetGeometry(const char*);
	};
}