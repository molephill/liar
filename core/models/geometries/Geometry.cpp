
#include <core/models/geometries/Geometry.h>
#include <Liar3D.h>
#include <algorithm>

namespace Liar
{
	Geometry::Geometry(Liar::GeometryVertexType geometryType, GLenum type) :
		Liar::Resource(),
		m_geometryVertexType(geometryType),
		m_bufferSubType(type),
		m_rawVertexBuffers(nullptr),
		m_vertexArray(0), m_vertexBuffer(0), m_elementBuffer(0)
	{
	}

	Geometry::~Geometry()
	{
		Destroy();
	}

	void Geometry::RecreateResource()
	{
		Liar::Resource::RecreateResource();
		m_rawVertexBuffers = Liar::Liar3D::geometryFactory->GetVertexFactory().GetRawVertexBuffers(m_geometryVertexType);

		// 创建具体的数据
		if (RecreateSubResource())
		{
			// 提交数据
			UploadData();
		}
	}

	void Geometry::DisposeResource()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		if (m_vertexArray > 0) gl.DeleteBuffers(1, &m_vertexArray);
		if (m_vertexBuffer > 0) gl.DeleteBuffers(1, &m_vertexBuffer);
		if (m_elementBuffer > 0) gl.DeleteBuffers(1, &m_elementBuffer);

		if (m_rawVertexBuffers)
		{
			delete m_rawVertexBuffers;
			m_rawVertexBuffers = nullptr;
		}
	}

	void Geometry::UploadData()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		gl.GenVertexArrays(1, &m_vertexArray);
		gl.BindVertexArray(m_vertexArray);

		gl.GenBuffers(1, &m_vertexBuffer);
		gl.BindBuffer(m_bufferSubType, m_vertexBuffer);

		gl.GenBuffers(1, &m_elementBuffer);
		gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

		size_t bufferSize = m_rawVertexBuffers->GetBufferSize();
		gl.BufferData(m_bufferSubType, bufferSize, nullptr, GL_STATIC_DRAW);

		// 提交顶点数据
		m_rawVertexBuffers->UploadData(m_bufferSubType);
	}

	void Geometry::SetGeometryVertexType(Liar::GeometryVertexType geometryVertexType)
	{
		if (m_geometryVertexType != geometryVertexType)
		{
			m_geometryVertexType = geometryVertexType;
			DisposeResource();
			RecreateResource();
		}
	}

	Liar::Uint Geometry::GetNumberTriangles() const
	{
		return m_rawVertexBuffers->GetNumberTriangles();
	}

	Liar::Uint Geometry::GetNumberLength() const 
	{
		return m_rawVertexBuffers->GetNumberLength();
	}

	void Geometry::Draws()
	{
		glBindVertexArray(m_vertexArray);
		glDrawElements(GL_TRIANGLES, GetNumberLength(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}