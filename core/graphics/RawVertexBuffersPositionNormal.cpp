#include <core/graphics/RawVertexBuffersPositionNormal.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositionNormal::RawVertexBuffersPositionNormal(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normal(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositionNormal::~RawVertexBuffersPositionNormal()
	{
		delete m_normal;
		m_normal = nullptr;
	}

	Liar::Int RawVertexBuffersPositionNormal::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_normal->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionNormal::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionNormal::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionNormal::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) m_normal->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionNormal::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) return m_normal->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	size_t RawVertexBuffersPositionNormal::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		return m_normal->UploadData(gl, type, offset, 
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
	}

	size_t RawVertexBuffersPositionNormal::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		return m_normal->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, gl, stride, offset);
	}
}
