#pragma once

#include <core/models/geometries/Geometry.h>
#include <core/graphics/VertexFactory.h>

namespace Liar
{
	class GeometryFactory
	{
	public:
		GeometryFactory();
		~GeometryFactory();

	private:
		Liar::VertexFactory* m_vertexFactory;

	public:
		Liar::VertexFactory& GetVertexFactory() { return *m_vertexFactory; };
		Liar::Geometry* GetGeometry(Liar::GeometryType);
		Liar::Int GetVertexNumberFloat(Liar::GeometryVertexType);
	};
}