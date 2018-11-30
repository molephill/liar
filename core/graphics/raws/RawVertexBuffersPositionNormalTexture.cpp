
#include <core/graphics/raws/RawVertexBuffersPositionNormalTexture.h>

namespace Liar
{
	RawVertexBuffersPositionNormalTexture::RawVertexBuffersPositionNormalTexture():
		Liar::IRawVertexBuffers(),
		m_positons(nullptr), m_normals(nullptr), m_texCoords(nullptr),
		m_numberPostions(0), m_numberNormals(0), m_numberTexCoodrs(0)
	{
	}

	RawVertexBuffersPositionNormalTexture::~RawVertexBuffersPositionNormalTexture()
	{
		Destroy();
	}

	void RawVertexBuffersPositionNormalTexture::Destroy()
	{
		size_t i = 0;
		for (i = 0; i < m_numberPostions; ++i)
		{
			delete m_positons[i];
			m_positons[i] = nullptr;
		}

		if (m_positons) free(m_positons);
		m_positons = nullptr;

		for (i = 0; i < m_numberNormals; ++i)
		{
			delete m_normals[i];
			m_normals[i] = nullptr;
		}
		if (m_normals) free(m_normals);
		m_normals = nullptr;

		for (i = 0; i < m_numberTexCoodrs; ++i)
		{
			delete m_texCoords[i];
			m_texCoords[i] = nullptr;
		}
		if (m_texCoords) free(m_texCoords);
		m_texCoords = nullptr;
	}

	void RawVertexBuffersPositionNormalTexture::AddPositonVertex(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, (void**)m_positons, m_numberPostions, x, y, z);
		Liar::Vector3* positon = static_cast<Liar::Vector3*>(buffer);
		if (!positon)
		{
			++m_numberPostions;
			if (!m_positons) m_positons = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*));
			else m_positons = (Liar::Vector3**)realloc(m_positons, sizeof(Liar::Vector3*)*m_numberPostions);
			positon = new Liar::Vector3(x, y, z);
			m_positons[m_numberPostions - 1] = positon;
		}
	}

	void RawVertexBuffersPositionNormalTexture::AddNormalVertex(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, (void**)m_normals, m_numberNormals, x, y, z);
		Liar::Vector3* normal = static_cast<Liar::Vector3*>(buffer);
		if (!normal)
		{
			++m_numberNormals;
			if (!m_normals) m_normals = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*));
			else m_normals = (Liar::Vector3**)realloc(m_normals, sizeof(Liar::Vector3*)*m_numberNormals);
			normal = new Liar::Vector3(x, y, z);
			m_normals[m_numberNormals - 1] = normal;
		}
	}

	void RawVertexBuffersPositionNormalTexture::AddTexCoordVertex(Liar::Number x, Liar::Number y)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, (void**)m_texCoords, m_numberTexCoodrs, x, y);
		Liar::Vector2* texCoord = static_cast<Liar::Vector2*>(buffer);
		if (!texCoord)
		{
			++m_numberTexCoodrs;
			if (!m_texCoords) m_texCoords = (Liar::Vector2**)malloc(sizeof(Liar::Vector2*));
			else m_texCoords = (Liar::Vector2**)realloc(m_texCoords, sizeof(Liar::Vector2*)*m_numberTexCoodrs);
			texCoord = new Liar::Vector2(x, y);
			m_texCoords[m_numberTexCoodrs - 1] = texCoord;
		}
	}

	void RawVertexBuffersPositionNormalTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			AddPositonVertex(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			AddNormalVertex(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			AddTexCoordVertex(x, y);
			break;
		}
	}

	void* RawVertexBuffersPositionNormalTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			return m_positons[index];
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normals[index];
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			return m_texCoords[index];
			break;
		default:
			return nullptr;
		}
	}
}