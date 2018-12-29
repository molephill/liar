
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
		m_preCompileShader = Liar::Liar3D::shaderCompile->GetPreCompileShader("TEST");
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

	void Mesh::SetGeometryType(Liar::GeometryType type)
	{
		Release();
		m_geometry = Liar::Liar3D::geometryFactory->GetGeometry(type);
	}

	void Mesh::SetGeometryType(const char* path)
	{
		Release();
		m_geometry = Liar::Liar3D::geometryFactory->GetGeometry(path);
	}

	void Mesh::SetSharedMaterials(Liar::BaseMaterial* shared)
	{
		m_sharedMaterial = shared;
	}

	Liar::RenderUnit* Mesh::GetRenderUint(Liar::RenderState& state)
	{
		Liar::RenderUnit* renderUnit = Liar::Node::GetRenderUint(state);
		renderUnit->geometry = m_geometry;
		renderUnit->material = m_sharedMaterial;
		return renderUnit;
	}
}