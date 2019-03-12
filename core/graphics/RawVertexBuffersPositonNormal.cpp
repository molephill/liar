#include <core/graphics/RawVertexBuffersPositonNormal.h>

namespace Liar
{
	VertexPositionNormalKey::VertexPositionNormalKey() :
		Liar::VertexPositionKey(),
		m_normalIndex(0)
	{}

	void VertexPositionNormalKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normalIndex = index;
			break;
		default:
			Liar::VertexPositionKey::SetVertexIndex(attr, index);
			break;
		}
	}

	Liar::Uint VertexPositionNormalKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normalIndex;
		default:
			return Liar::VertexPositionKey::GetVertexIndex(attr);
		}
	}

	Liar::Boolen VertexPositionNormalKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return	m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) && Liar::VertexPositionKey::operator==(rhs);
	}

	Liar::IVertexKey* VertexPositionNormalKey::Clone() const
	{
		Liar::VertexPositionNormalKey* tmp = new Liar::VertexPositionNormalKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_normalIndex);
		return tmp;
	}

	void VertexPositionNormalKey::PrintData()
	{
		Liar::VertexPositionKey::PrintData();
		std::cout << "," << m_normalIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositonNormal::RawVertexBuffersPositonNormal(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normals(nullptr), m_numberNormals(0)
	{
	}


	RawVertexBuffersPositonNormal::~RawVertexBuffersPositonNormal()
	{
		if (m_normals)
		{
			for (size_t i = 0; i < m_numberNormals; ++i)
			{
				delete m_normals[i];
				m_normals[i] = nullptr;
			}
			free(m_normals);
			m_normals = nullptr;
		}
	}

	void RawVertexBuffersPositonNormal::AddNormalVertex(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, (void**)m_normals, m_numberNormals, x, y, z);
		Liar::Vector3* normal = static_cast<Liar::Vector3*>(buffer);
		if (!normal)
		{
			++m_numberNormals;
			size_t blockSize = sizeof(Liar::Vector3*)*m_numberNormals;
			if (!m_normals) m_normals = (Liar::Vector3**)malloc(blockSize);
			else m_normals = (Liar::Vector3**)realloc(m_normals, blockSize);
			normal = new Liar::Vector3(x, y, z);
			m_normals[m_numberNormals - 1] = normal;
		}
	}

	void RawVertexBuffersPositonNormal::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			AddNormalVertex(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, x, y, z, w);
			break;
		}
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_numberNormals = len;
			m_normals = (Liar::Vector3**)realloc(m_normals, sizeof(Liar::Vector3*)*m_numberNormals);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
			break;
		}
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normals[index] = new Liar::Vector3(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, x, y, z);
			break;
		}
	}

	void* RawVertexBuffersPositonNormal::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normals[index];
		default:
			return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
		}
	}

	Liar::Int RawVertexBuffersPositonNormal::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
	}

	size_t RawVertexBuffersPositonNormal::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		size_t normalOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
		gl.BufferSubData(type, normalOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
		return normalOffsize;
	}

	size_t RawVertexBuffersPositonNormal::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		size_t normalOffsize = positionOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);
		return normalOffsize;
	}
}
