#include <core/graphics/RawVertexBuffersPosition.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionKey::VertexPositionKey() :
		m_positonIndex(0)
	{}

	void VertexPositionKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_positonIndex = index;
			break;
		default:
			break;
		}
	}

	Liar::Uint VertexPositionKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			return m_positonIndex;
		default:
			return 0;
		}
	}

	Liar::Boolen VertexPositionKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return	m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionKey::Clone() const
	{
		Liar::VertexPositionKey* tmp = new Liar::VertexPositionKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		return tmp;
	}

	void VertexPositionKey::PrintData()
	{
		//std::cout << "posIndex: " << m_positonIndex << " normalIndex: " << m_normalIndex << " texIndex: " << m_texCoordIndex;
		std::cout << m_positonIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPosition::RawVertexBuffersPosition(Liar::GeometryVertexType type):
		Liar::IRawVertexBuffers(type),
		m_positons(nullptr), m_numberPostions(0)
	{
	}

	RawVertexBuffersPosition::~RawVertexBuffersPosition()
	{
		if (m_positons)
		{
			for (size_t i = 0; i < m_numberPostions; ++i)
			{
				delete m_positons[i];
				m_positons[i] = nullptr;
			}
			free(m_positons);
			m_positons = nullptr;
		}
	}

	void RawVertexBuffersPosition::AddPositonVertex(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, (void**)m_positons, m_numberPostions, x, y, z);
		Liar::Vector3* positon = static_cast<Liar::Vector3*>(buffer);
		if (!positon)
		{
			++m_numberPostions;
			size_t blockSize = sizeof(Liar::Vector3*)*m_numberPostions;
			if (!m_positons) m_positons = (Liar::Vector3**)malloc(blockSize);
			else m_positons = (Liar::Vector3**)realloc(m_positons, blockSize);
			positon = new Liar::Vector3(x, y, z);
			m_positons[m_numberPostions - 1] = positon;
		}
	}

	void RawVertexBuffersPosition::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			AddPositonVertex(x, y, z);
			break;
		default:
			break;
		}
	}

	void RawVertexBuffersPosition::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_numberPostions = len;
			m_positons = (Liar::Vector3**)realloc(m_positons, sizeof(Liar::Vector3*)*m_numberPostions);
			break;
		default:
			Liar::IRawVertexBuffers::SetSubVertexBufferLen(attr, len);
			break;
		}
	}

	void RawVertexBuffersPosition::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_positons[index] = new Liar::Vector3(x, y, z);
			break;
		default:
			Liar::IRawVertexBuffers::SetSubVertexBuffer(attr, index, x, y, z);
			break;
		}
	}

	void* RawVertexBuffersPosition::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			return m_positons[index];
			break;
		default:
			return nullptr;
		}
	}

	Liar::Int RawVertexBuffersPosition::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
	}

	size_t RawVertexBuffersPosition::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = start;
		gl.BufferSubData(type, positionOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION));
		return positionOffsize;
	}

	size_t RawVertexBuffersPosition::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t positonOffsie = 0;
		// position
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)positonOffsie);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION);
		return positonOffsie;
	}

	void RawVertexBuffersPosition::UploadSubData(GLenum type)
	{
		Liar::Int stride = GetStride();
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		for (Liar::Int i = 0; i < m_numberVertexKeys; ++i)
		{
			size_t start = i * stride;
			LoopUploadSubData(gl, type, i, start);
		}
	}

	void RawVertexBuffersPosition::VertexAttrbPointer()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t stride = GetStride();
		VertexAttrbSubPointer(gl, stride);
	}

	void RawVertexBuffersPosition::PrintData()
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
