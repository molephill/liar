
#include <core/models/Mesh.h>
#include <Liar3D.h>

namespace Liar
{
	Mesh::Mesh(Liar::GeometryType type):
		Liar::TransformNode()
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

	bool Mesh::Destroy(bool destroyChild)
	{
		bool destroy = Liar::TransformNode::Destroy(destroyChild);
		if (destroy)
		{
			m_geometry->ReduceRefrence();
			m_geometry = nullptr;
		}
		return destroy;
	}

	bool Mesh::Render(Liar::StageContext& gl, Liar::RenderState& state)
	{
		bool render = Liar::TransformNode::Render(gl, state);
		if (render) render = m_geometry->Render(gl, state);
		return render;
	}
}