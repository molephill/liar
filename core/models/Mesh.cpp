
#include <core/models/Mesh.h>
#include <Liar3D.h>

namespace Liar
{
	Mesh::Mesh(Liar::GeometryType type):
		Liar::Node()
	{
		SetGeometryType(type);
	}


	Mesh::~Mesh()
	{
		Destroy();
	}

	void Mesh::SetGeometryType(Liar::GeometryType type)
	{
		if (m_geometry)
		{
			m_geometry->ReduceRefrence();
			m_geometry = nullptr;
		}
		m_geometry = Liar::Liar3D::geometryFactory->GetGeometry(type);
	}

	Liar::RenderUnit* Mesh::GetRenderUint()
	{
		Liar::RenderUnit* renderUnit = Liar::Node::GetRenderUint();
		renderUnit->geometry = m_geometry;
		return renderUnit;
	}

	Liar::Int Mesh::CollectRenderUint(Liar::RenderState& state)
	{
		Liar::Liar3D::rendering->AddRenderUnit(GetRenderUint());
		return CollectChildrenRenderUint(state) + 1;
	}

	bool Mesh::Destroy(bool destroyChild)
	{
		bool destroy = Liar::Node::Destroy(destroyChild);
		if (destroy)
		{
			m_geometry->ReduceRefrence();
			m_geometry = nullptr;
		}
		return destroy;
	}
}