#pragma once

#include <core/display/TransformNode.h>
#include <core/models/GeometryFactory.h>

namespace Liar
{
	class Mesh:public TransformNode
	{
	public:
		Mesh(Liar::GeometryType);
		virtual ~Mesh();

	protected:
		Liar::Geometry* m_geometry;

	public:
		void SetGeometryType(Liar::GeometryType);
		virtual bool Render(Liar::StageContext& gl, Liar::RenderState& state);
		virtual bool Destroy(bool destroyChild = true);
	};
}