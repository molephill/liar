#include <core/graphics/RawVertexBuffersPositonNormal.h>

namespace Liar
{
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

	Liar::Int RawVertexBuffersPositonNormal::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_normal->GetSize();
	}

	// 设置 buffer 信息
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

	// 取得 buffer
	void* RawVertexBuffersPositonNormal::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) return m_normal->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
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
		size_t positionOffset = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int normalSize = m_normal->GetSize();
		size_t normalOffset = positionOffset + m_position->GetSize();
		void* normal = GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL);
		gl.BufferSubData(type, normalOffset, normalSize, normal);
		return normalOffset;
	}

	size_t RawVertexBuffersPositonNormal::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffset = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// normal
		size_t normalOffset = positionOffset + m_position->GetSize();
		Liar::Int normalFormat = m_normal->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, normalFormat, GL_FLOAT, GL_FALSE, stride, (void*)normalOffset);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);
		return normalOffset;
	}
}
