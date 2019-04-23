#pragma once

#include <core/display/Node.h>
#include <core/material/BaseMaterial.h>

namespace Liar
{
	class Mesh:public Liar::Node
	{
	public:
		Mesh();
		virtual ~Mesh();

	protected:
		Liar::Geometry* m_geometry;
		Liar::BaseMaterial* m_sharedMaterial;

		virtual Liar::RenderUnit* GetRenderUint(Liar::RenderState&);
		virtual void SetGeometry(Liar::Geometry*, Liar::BaseMaterial** = nullptr);

	public:
		void SetGeometryType(const char*, Liar::BaseMaterial** = nullptr);

		void SetSharedMaterials(Liar::BaseMaterial*);

		Liar::Geometry* GetGeometry() { return m_geometry; };
		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
		virtual Liar::ClassType GetNodeType() const { return Liar::ClassType::CLASS_NODE_TYPE_MESH; };
	};
}