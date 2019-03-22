#include <core/graphics/RawVertexBuffersPositonNormal.h>

namespace Liar
{
	/*
	* ��������
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

	// ����normal��Ϣ
	void RawVertexBuffersPositonNormal::AddNormalVertexBuffer(Liar::IHeapOperator* data)
	{
		m_normal->AddVertexBuffer(data);
	}

	// ����normal��Ϣ
	void RawVertexBuffersPositonNormal::SetNormalVertexBuffer(Liar::Int index, Liar::IHeapOperator* data)
	{
		m_normal->SetVertexBuffer(index, data);
	}

	// ����normal����
	void RawVertexBuffersPositonNormal::SetNormalVertexBufferLen(Liar::Int len)
	{
		m_normal->SetVertexBufferLen(len);
	}

	// ���normal��Ϣ
	void* RawVertexBuffersPositonNormal::GetNormalVertexBuffer(size_t index) const
	{
		return m_normal->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositonNormal::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + m_normal->GetStride();
	}

	// ���� buffer ��Ϣ
	void RawVertexBuffersPositonNormal::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) AddNormalVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) SetNormalVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) SetNormalVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPositonNormal::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) return GetNormalVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	// ����ύָ������������Ϣ
	void* RawVertexBuffersPositonNormal::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return Liar::RawVertexBuffersPosition::GetUploadVertexBuffer(index, attr);
		}
	}

	size_t RawVertexBuffersPositonNormal::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int normalOffset = m_normal->GetStride();
		size_t normalOffsize = positionOffsize + m_position->GetStride();

		gl.BufferSubData(type, normalOffsize, normalOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
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
