
#include <core/models/Mesh.h>
#include <Liar3D.h>

namespace Liar
{
	Mesh::Mesh(Liar::GeometryType type):
		Liar::Node(),
		m_sharedMaterial(nullptr),
		m_geometry(nullptr)
	{
		SetGeometryType(type);
	}


	Mesh::~Mesh()
	{
		Release();
	}

	void Mesh::Release()
	{
		if (m_geometry)
		{
			m_geometry->ReduceRefrence();
			m_geometry = nullptr;
		}
	}

	void Mesh::SetGeometryType(Liar::GeometryType type, Liar::BaseMaterial** materials)
	{
		SetGeometry(Liar::Liar3D::mtl->GetGeometry(type), materials);
	}

	void Mesh::SetGeometryType(const char* path, Liar::BaseMaterial** materials)
	{
		SetGeometry(Liar::Liar3D::mtl->GetGeometry(path), materials);
	}

	void Mesh::SetGeometry(Liar::Geometry* geometry, Liar::BaseMaterial** materials)
	{
		Release();
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