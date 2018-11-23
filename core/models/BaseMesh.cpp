
#include <core/models/BaseMesh.h>
#include <Liar3D.h>
#include <algorithm>

namespace Liar
{
	BaseMesh::BaseMesh(GLenum type):
		Liar::Resource(),
		m_bufferSubType(type),
		m_rawVertexBuffers(nullptr), m_numberVertices(0),
		m_vertexArray(0), m_vertexBuffer(0), m_elementBuffer(0),
		m_vertices(nullptr), m_numberIndices(0)
	{
	}

	BaseMesh::~BaseMesh()
	{

	}

	void BaseMesh::DisposeResource()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		if (m_vertexArray > 0) gl.DeleteBuffers(1, &m_vertexArray);
		if (m_vertexBuffer > 0) gl.DeleteBuffers(1, &m_vertexBuffer);
		if (m_elementBuffer > 0) gl.DeleteBuffers(1, &m_elementBuffer);

		for (size_t i = 0; i < m_numberVertices; ++i)
		{
			m_vertices[i]->~IVertexBuffer();
			m_vertices[i] = nullptr;
		}
		if (m_vertices) free(m_vertices);
		m_vertices = nullptr;

		if (m_rawVertexBuffers)
		{
			m_rawVertexBuffers->~IRawVertexBuffers();
			free(m_rawVertexBuffers);
			m_rawVertexBuffers = nullptr;
		}

		if (m_indices) free(m_indices);
		m_indices = nullptr;
	}

	void BaseMesh::GenAndBindVertex()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		gl.GenVertexArrays(1, &m_vertexArray);
		gl.BindVertexArray(m_vertexArray);

		gl.GenBuffers(1, &m_vertexBuffer);
		gl.BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		// indices data
		size_t indicesSize = m_numberIndices * sizeof(Liar::Uint);
		gl.GenBuffers(1, &m_elementBuffer);
		gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
		gl.BufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_indices, GL_STATIC_DRAW);

		// vertex data
		size_t i = 0;
		size_t stride = m_vertices[i]->GetStride();
		size_t bufferSize = m_numberVertices * stride;
		gl.BufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);

		for (i = 0; i < m_numberVertices; ++i)
		{
			size_t start = i * stride;
			m_vertices[i]->BufferSubData(m_bufferSubType, start);
		}
	}

	size_t BaseMesh::GetRenderElementsCount()
	{
		return 1;
	}

	const Liar::IRenderable* BaseMesh::GetRenderElement(size_t) const
	{
		return this;
	}

	void BaseMesh::BeforeRender(Liar::RenderState&)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		gl.BindVertexArray(m_vertexArray);
	}
}