
#include <core/models/Mesh.h>
#include <Liar3D.h>

namespace Liar
{
	Mesh::Mesh():
		Liar::Node(),
		m_sharedMaterial(nullptr),
		m_geometry(nullptr)
	{
	}


	Mesh::~Mesh()
	{
		Liar::Liar3D::mtl->ReduceRefrence(m_geometry);
		m_geometry = nullptr;
	}

	void Mesh::SetGeometryType(const char* path, Liar::BaseMaterial** materials)
	{
		Liar::GeometryType type = Liar::GeometryType::GEOMETRY_NET;
		Liar::Geometry* geo = static_cast<Liar::Geometry*>(Liar::Liar3D::mtl->CreateResource(path, Liar::ClassType::CLASS_NODE_TYPE_GEOMETORY, &type));
		geo->SetURL(path);
		SetGeometry(geo, materials);
	}

	void Mesh::SetGeometry(Liar::Geometry* geometry, Liar::BaseMaterial** materials)
	{
		Liar::Liar3D::mtl->ReduceRefrence(m_geometry);
		m_geometry = geometry;
		if (m_geometry && materials)
		{
			Liar::IRawVertexBuffers* raw = m_geometry->GetRawVertexBuffers();
			if (raw) SetSharedMaterials(materials[raw->GetMtlIndex()]);
		}
	}

	void Mesh::SetSharedMaterials(Liar::BaseMaterial* shared)
	{
		m_sharedMaterial = shared;
	}

	Liar::Int Mesh::CollectRenderUint(Liar::RenderState& state)
	{
		if (!m_geometry || !m_geometry->GetUploaded()) return 0;
		return Liar::Node::CollectRenderUint(state);
	}

	Liar::RenderUnit* Mesh::GetRenderUint(Liar::RenderState& state)
	{
		Liar::RenderUnit* renderUnit = Liar::Node::GetRenderUint(state);
		renderUnit->geometry = m_geometry;
		renderUnit->material = m_sharedMaterial;
		return renderUnit;
	}
}