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
		virtual Liar::RenderUnit* GetRenderUint(Liar::RenderState&, bool buildShader = true);
		virtual bool BuildShaderProgram(Liar::RenderState&);

	public:
		virtual Liar::Int CollectRenderUint(Liar::RenderState&, bool buildShader = true);
		void SetGeometryType(Liar::GeometryType);
	};
}