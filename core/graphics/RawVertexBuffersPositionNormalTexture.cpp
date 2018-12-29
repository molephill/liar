
#include <core/graphics/RawVertexBuffersPositionNormalTexture.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionNormalTextureKey::VertexPositionNormalTextureKey() :
		m_positonIndex(0), m_normalIndex(0), m_texCoordIndex(0)
	{}

	void VertexPositionNormalTextureKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_positonIndex = index;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normalIndex = index;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			m_texCoordIndex = index;;
			break;
		}
	}

	Liar::Uint VertexPositionNormalTextureKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			return m_positonIndex;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normalIndex;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			return m_texCoordIndex;;
			break;
		default:
			return 0;
		}
	}

	Liar::Boolen VertexPositionNormalTextureKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) &&
			m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) &&
			m_texCoordIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE);
	}

	Liar::IVertexKey* VertexPositionNormalTextureKey::Clone() const
	{
		Liar::VertexPositionNormalTextureKey* tmp = new Liar::VertexPositionNormalTextureKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_normalIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_texCoordIndex);
		return tmp;
	}

	void VertexPositionNormalTextureKey::PrintData()
	{
		//std::cout << "posIndex: " << m_positonIndex << " normalIndex: " << m_normalIndex << " texIndex: " << m_texCoordIndex;
		std::cout << m_positonIndex << "," << m_normalIndex << "," << m_texCoordIndex << ")";
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositionNormalTexture::RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type):
		Liar::IRawVertexBuffers(type),
		m_positons(nullptr), m_normals(nullptr), m_texCoords(nullptr),
		m_numberPostions(0), m_numberNormals(0), m_numberTexCoodrs(0)
	{
	}

	RawVertexBuffersPositionNormalTexture::~RawVertexBuffersPositionNormalTexture()
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

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_numberPostions = len;
			m_positons = (Liar::Vector3**)realloc(m_positons, sizeof(Liar::Vector3*)*m_numberPostions);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_numberNormals = len;
			m_normals = (Liar::Vector3**)realloc(m_normals, sizeof(Liar::Vector3*)*m_numberNormals);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			m_numberTexCoodrs = len;
			m_texCoords = (Liar::Vector2**)realloc(m_texCoords, sizeof(Liar::Vector2*)*m_numberTexCoodrs);
			break;
		default:
			Liar::IRawVertexBuffers::SetSubVertexBufferLen(attr, len);
			break;
		}
	}

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_positons[index] = new Liar::Vector3(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normals[index] = new Liar::Vector3(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			m_texCoords[index] = new Liar::Vector2(x, y);
			break;
		default:
			Liar::IRawVertexBuffers::SetSubVertexBuffer(attr, index, x, y, z);
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

	Liar::Int RawVertexBuffersPositionNormalTexture::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
	}

	void RawVertexBuffersPositionNormalTexture::UploadSubData(GLenum type)
	{
		Liar::Int stride = GetStride();
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		for (Liar::Int i = 0; i < m_numberVertexKeys; ++i)
		{
			size_t start = i * stride;
			size_t positionOffsize = start;
			size_t normalOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
			size_t texCoordOffseize = normalOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;

			gl.BufferSubData(type, positionOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION));
			gl.BufferSubData(type, normalOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
			gl.BufferSubData(type, texCoordOffseize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		}
	}

	void RawVertexBuffersPositionNormalTexture::VertexAttrbPointer()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t stride = Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 * 2 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
		size_t positionOffsize = 0;
		size_t normalOffsize = positionOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		size_t texCoordOffseize = normalOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		// position
		gl.VertexAttribPointer(0, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)positionOffsize);
		gl.EnableVertexAttribArray(0);
		// normal
		gl.VertexAttribPointer(1, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(1);
		// texCoordinate
		gl.VertexAttribPointer(2, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR2, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffseize);
		gl.EnableVertexAttribArray(2);
	}

	void RawVertexBuffersPositionNormalTexture::PrintData()
	{
		std::cout << "indices:\n";
		Liar::Int i = 0;
		for (i = 0; i < m_numberIndices; ++i)
		{
			std::cout << "index: " << i << " : " << m_indices[i] << "\n";
		}
		std::cout << "vertex:\n";
		for (i = 0; i < m_numberVertexKeys; ++i)
		{
			std::cout << "index: " << i << " : ";
			m_vertexKeys[i]->PrintData();
			std::cout << "\n";
		}
	}
}