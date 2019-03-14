#include <core/graphics/RawVertexBuffersPositonNormal.h>

namespace Liar
{
	VertexPositionNormalKey::VertexPositionNormalKey() :
		Liar::VertexPositionKey(),
		m_normalIndex(0)
	{}

	Liar::Boolen VertexPositionNormalKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) &&
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
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
		std::cout << m_positonIndex << "," << m_normalIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositonNormal::RawVertexBuffersPositonNormal(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normal(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositonNormal::~RawVertexBuffersPositonNormal()
	{
		delete m_normal;
		m_normal = nullptr;
	}

	// 增加normal信息
	void RawVertexBuffersPositonNormal::AddNormalVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_normal->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPositonNormal::AddNormalVertexBuffer(const Liar::Vector3& normal)
	{
		AddNormalVertexBuffer(normal.x, normal.y, normal.z);
	}

	// 设置normal信息
	void RawVertexBuffersPositonNormal::SetNormalVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z)
	{
		SetNormalVertexBuffer(index, new Liar::Vector3(x, y, z));
	}

	void RawVertexBuffersPositonNormal::SetNormalVertexBuffer(size_t index, Liar::Vector3* normal)
	{
		m_normal->SetVertexBuffer(index, normal);
	}

	// 设置normal长度
	void RawVertexBuffersPositonNormal::SetNormalVertexBufferLen(Liar::Int len)
	{
		m_normal->SetVertexBufferLen(len);
	}

	// 获得normal信息
	void* RawVertexBuffersPositonNormal::GetNormalVertexBuffer(size_t index) const
	{
		return m_normal->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositonNormal::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + m_normal->GetStride();
	}

	size_t RawVertexBuffersPositonNormal::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetStride();
		Liar::Int normalOffset = m_normal->GetStride();

		size_t normalOffsize = positionOffsize + positionOffset;
		gl.BufferSubData(type, normalOffsize, normalOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return normalOffsize;
	}

	size_t RawVertexBuffersPositonNormal::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// normal
		size_t normalOffisze = positionOffsize + m_position->GetStride();
		Liar::Int normalFormat = m_normal->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, normalFormat, GL_FLOAT, GL_FALSE, stride, (void*)normalOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);

		return normalOffisze;
	}
}
