
#include <core/render/RenderUnit.h>

namespace Liar
{
	RenderUnit::RenderUnit() :
		transform(nullptr), shaderProgram(nullptr),
		m_geometries(nullptr), m_numberGeometries(0),
		m_materials(nullptr), m_numberMaterials(0)
	{
	}

	RenderUnit::~RenderUnit()
	{
		Clear();
	}

	void RenderUnit::Clear()
	{
		transform = nullptr;
		shaderProgram = nullptr;

		Liar::Int i = 0;
		for (i = 0; i < m_numberGeometries; ++i) m_geometries[i] = nullptr;
		if (m_geometries) free(m_geometries);
		m_geometries = nullptr;
		m_numberGeometries = 0;

		for (i = 0; i < m_numberMaterials; ++i) m_materials[i] = nullptr;
		if (m_materials) free(m_materials);
		m_materials = nullptr;
		m_numberMaterials = 0;
	}

	void RenderUnit::AddGeometry(Liar::Geometry* geo)
	{
		++m_numberGeometries;
		size_t size = sizeof(Liar::Geometry*)*m_numberGeometries;
		if (m_geometries) m_geometries = (Liar::Geometry**)realloc(m_geometries, size);
		else m_geometries = (Liar::Geometry**)malloc(size);
		m_geometries[m_numberGeometries - 1] = geo;
	}

	void RenderUnit::AddMaterial(Liar::BaseMaterial* mat)
	{
		++m_numberMaterials;
		size_t size = sizeof(Liar::BaseMaterial*)*m_numberMaterials;
		if (m_materials) m_materials = (Liar::BaseMaterial**)realloc(m_materials, size);
		else m_materials = (Liar::BaseMaterial**)malloc(size);
		m_materials[m_numberGeometries - 1] = mat;
	}

	void RenderUnit::Render(Liar::RenderState& state)
	{
		shaderProgram->Use();
		shaderProgram->SetMat4("u_MvpMatrix", transform->GetProjectionViewWorldMatrix());
		
		Liar::Int i = 0;
		for (i = 0; i < m_numberGeometries; ++i) m_geometries[i]->Draws();
	}
}