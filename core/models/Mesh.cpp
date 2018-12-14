
#include <core/models/Mesh.h>
#include <Liar3D.h>

namespace Liar
{
	Mesh::Mesh(Liar::GeometryType type):
		Liar::Node()
	{
		SetGeometryType(type);
		m_preCompileShader = Liar::Liar3D::shaderCompile->GetPreCompileShader("TEST");
	}


	Mesh::~Mesh()
	{
		m_geometry->ReduceRefrence();
		m_geometry = nullptr;
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

	bool Mesh::BuildShaderProgram(Liar::RenderState& state)
	{
		if (!m_shaderProgram) m_shaderProgram = new Liar::ShaderProgram();
		bool recreate = Liar::Node::BuildShaderProgram(state);
		if (!recreate) recreate = m_shaderProgram->vertexDefine >= 0;
		if (recreate)
		{
			m_shaderProgram->Clear();
			m_shaderProgram->vertexDefine = 0;
			m_shaderProgram->fragementDefine = m_material ? m_material->GetShaderValue().GetShaderDefineValue() : m_shaderProgram->fragementDefine;

			std::string vertexCode(Liar::Liar3D::shaderCompile->GetVersion());
			vertexCode += m_geometry->GetAttribDefines();
			vertexCode += m_preCompileShader->vertexShaderCode;

			std::string fragmentCode(Liar::Liar3D::shaderCompile->GetVersion());
			fragmentCode += m_preCompileShader->fragmentShaderCode;

			m_shaderProgram->LinkProgram(vertexCode.c_str(), fragmentCode.c_str());
		}

		return recreate;
	}

	Liar::RenderUnit* Mesh::GetRenderUint(Liar::RenderState& state, bool buildShader)
	{
		Liar::RenderUnit* renderUnit = Liar::Node::GetRenderUint(state, buildShader);
		renderUnit->geometry = m_geometry;
		return renderUnit;
	}
}