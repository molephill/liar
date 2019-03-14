#include <core/graphics/RawVertexBuffersPosition.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionKey::VertexPositionKey() :
		m_positonIndex(0)
	{}

	Liar::Boolen VertexPositionKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionKey::Clone() const
	{
		Liar::VertexPositionKey* tmp = new Liar::VertexPositionKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		return tmp;
	}

	void VertexPositionKey::PrintData()
	{
		std::cout << m_positonIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPosition::RawVertexBuffersPosition(Liar::GeometryVertexType type):
		Liar::IRawVertexBuffers(type),
		m_position(new Liar::SubVector3VertexBuffer())
	{
	}

	RawVertexBuffersPosition::~RawVertexBuffersPosition()
	{
		delete m_position;
		m_position = nullptr;
	}

	Liar::Int RawVertexBuffersPosition::GetStride() const
	{
		return m_position->GetStride();
	}

	// 增加position信息
	void RawVertexBuffersPosition::AddPositionVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_position->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPosition::AddPositionVertexBuffer(const Liar::Vector3& pos)
	{
		AddPositionVertexBuffer(pos.x, pos.y, pos.z);
	}

	// 设置position信息
	void RawVertexBuffersPosition::SetPositionVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z)
	{
		SetPositionVertexBuffer(index, new Liar::Vector3(x, y, z));
	}

	void RawVertexBuffersPosition::SetPositionVertexBuffer(size_t index, Liar::Vector3* pos)
	{
		m_position->SetVertexBuffer(index, pos);
	}

	// 设置position长度
	void RawVertexBuffersPosition::SetPositionVertexBufferLen(Liar::Int len)
	{
		m_position->SetVertexBufferLen(len);
	}

	// 获得position信息
	void* RawVertexBuffersPosition::GetPostionVertexBuffer(size_t index) const
	{
		return m_position->GetVertexBuffer(index);
	}

	size_t RawVertexBuffersPosition::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = start;
		Liar::Int offset = m_position->GetStride();
		gl.BufferSubData(type, positionOffsize, offset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION));
		return positionOffsize;
	}

	size_t RawVertexBuffersPosition::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positonOffsie = 0;
		Liar::Int positonFormat = m_position->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION, positonFormat, GL_FLOAT, GL_FALSE, stride, (void*)positonOffsie);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION);
		return positonOffsie;
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
