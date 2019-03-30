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

	Liar::Int RawVertexBuffersPositonNormal::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_normal->GetSize();
	}

	// ���� buffer ��Ϣ
	void RawVertexBuffersPositonNormal::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositonNormal::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPositonNormal::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) return m_normal->GetVertexBuffer(index);
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
		size_t offset = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		return m_normal->UploadData(gl, type, offset, 
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
	}

	size_t RawVertexBuffersPositonNormal::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		return m_normal->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, gl, stride, offset);
	}
}
