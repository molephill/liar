
#include <core/models/geometries/Geometry.h>
#include <Liar3D.h>
#include <algorithm>

namespace Liar
{
	Geometry::Geometry(GLenum type):
		Liar::Resource(),
		m_geometryVertexType(Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE),
		m_bufferSubType(type),
		m_rawVertexBuffers(nullptr), m_numberVertices(0),
		m_vertexArray(0), m_vertexBuffer(0), m_elementBuffer(0),
		m_vertices(nullptr), m_numberIndices(0)
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
	}

	void Geometry::DisposeResource()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		if (m_vertexArray > 0) gl.DeleteBuffers(1, &m_vertexArray);
		if (m_vertexBuffer > 0) gl.DeleteBuffers(1, &m_vertexBuffer);
		if (m_elementBuffer > 0) gl.DeleteBuffers(1, &m_elementBuffer);

		for (size_t i = 0; i < m_numberVertices; ++i)
		{
			delete m_vertices[i];
			m_vertices[i] = nullptr;
		}
		if (m_vertices) free(m_vertices);
		m_vertices = nullptr;

		if (m_rawVertexBuffers)
		{
			delete m_rawVertexBuffers;
			m_rawVertexBuffers = nullptr;
		}

		if (m_indices) free(m_indices);
		m_indices = nullptr;
	}

	void Geometry::GenAndBindVertex()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
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

		for (i = 0; i < m_numberIndices; ++i)
		{
			size_t start = i * stride;
			size_t vertexIndex = m_indices[i];
			m_vertices[vertexIndex]->BufferSubData(m_bufferSubType, start);
		}

		m_vertices[0]->VertexAttrbPointer();
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

	Liar::IVertexBuffer* Geometry::GetVertexBuff(size_t index)
	{
		if (index >= m_numberVertices) return nullptr;
		return m_vertices[index];
	}

	Liar::Uint Geometry::GetNumberTriangles() 
	{
		return m_numberIndices / 3;
	}

	std::string Geometry::GetAttribDefines()
	{
		std::string tmp("#define ");
		tmp += Liar::VERTEX_ATTRIB_POSITION0;
		tmp += " 0\n";
		tmp += "#define ";
		tmp += Liar::VERTEX_ATTRIB_NORMAL0;
		tmp += " 1\n";
		tmp += "#define ";
		tmp += Liar::VERTEX_ATTRIB_TEXCOORDINATE0;
		tmp += " 2\n";
		return tmp;

		if (m_vertices) return m_vertices[0]->GetAttribDefines();
		else return "";
	}

	void Geometry::Draws()
	{
		glBindVertexArray(m_vertexArray);
		glDrawElements(GL_TRIANGLES, m_numberIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}