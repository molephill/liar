#pragma once

#include <core/display/Node.h>
#include <core/models/GeometryFactory.h>

namespace Liar
{
	class Mesh:public Liar::Node
	{
	public:
		Mesh(Liar::GeometryType);
		virtual ~Mesh();

	protected:
		Liar::Geometry* m_geometry;
		virtual Liar::RenderUnit* GetRenderUint();

	public:
		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
		void SetGeometryType(Liar::GeometryType);
		virtual bool Destroy(bool destroyChild = true);
	};
}