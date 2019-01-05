#pragma once

#include <core/display/Node.h>
#include <core/models/GeometryFactory.h>
#include <core/material/BaseMaterial.h>

namespace Liar
{
	class Mesh:public Liar::Node
	{
	public:
		Mesh(Liar::GeometryType);
		virtual ~Mesh();

	protected:
		Liar::Geometry* m_geometry;
		Liar::BaseMaterial* m_sharedMaterial;

		virtual Liar::RenderUnit* GetRenderUint(Liar::RenderState&);

		virtual void Release();

	public:
		void SetGeometryType(Liar::GeometryType);
		void SetGeometryType(const char*);

		void SetSharedMaterials(Liar::BaseMaterial*);

		Liar::Geometry* GetGeometry() { return m_geometry; };
		virtual Liar::ClassType GetNodeType() const { return Liar::ClassType::CLASS_NODE_TYPE_MESH; };
	};
}