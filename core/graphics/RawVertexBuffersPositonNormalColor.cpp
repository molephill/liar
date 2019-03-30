#include <core/graphics/RawVertexBuffersPositonNormalColor.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositonNormalColor::RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositonNormal(type),
		m_color(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositonNormalColor::~RawVertexBuffersPositonNormalColor()
	{
		delete m_color;
		m_color = nullptr;
	}

	Liar::Int RawVertexBuffersPositonNormalColor::GetSize() const
	{
		return  Liar::RawVertexBuffersPositonNormal::GetSize() + m_color->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositonNormalColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPositonNormal::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositonNormalColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) return m_color->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPositonNormal::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
	void* RawVertexBuffersPositonNormalColor::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return Liar::RawVertexBuffersPositonNormal::GetUploadVertexBuffer(index, attr);
		}
	}

	size_t RawVertexBuffersPositonNormalColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPositonNormal::LoopUploadSubData(gl, type, i, start);
		return m_color->UploadData(gl, type, offset,
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
	}

	size_t RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPositonNormal::VertexAttrbSubPointer(gl, stride);
		return m_color->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, gl, stride, offset);
	}
}
