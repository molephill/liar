#include <core/graphics/RawVertexBuffersPositonNormalColor.h>

namespace Liar
{
	/*
	* ��������
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

	// ����color��Ϣ
	void RawVertexBuffersPositonNormalColor::AddColorVertexBuffer(Liar::IHeapOperator* data)
	{
		m_color->AddVertexBuffer(data);
	}

	// ����color��Ϣ
	void RawVertexBuffersPositonNormalColor::SetColorVertexBuffer(Liar::Int index, Liar::IHeapOperator* data)
	{
		m_color->SetVertexBuffer(index, data);
	}

	// ����color����
	void RawVertexBuffersPositonNormalColor::SetColorVertexBufferLen(Liar::Int len)
	{
		m_color->SetVertexBufferLen(len);
	}

	// ���color��Ϣ
	void* RawVertexBuffersPositonNormalColor::GetColorVertexBuffer(size_t index) const
	{
		return m_color->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositonNormalColor::GetStride() const
	{
		return  Liar::RawVertexBuffersPositonNormal::GetStride() + m_color->GetStride();
	}

	// ���� buffer ��Ϣ
	void RawVertexBuffersPositonNormalColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) AddColorVertexBuffer(data);
		else Liar::RawVertexBuffersPositonNormal::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) SetColorVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) SetColorVertexBufferLen(len);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPositonNormalColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) return GetColorVertexBuffer(index);
		else return Liar::RawVertexBuffersPositonNormal::GetSubVertexBuffer(attr, index);
	}

	// ����ύָ������������Ϣ
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
		size_t normalOffsize = Liar::RawVertexBuffersPositonNormal::LoopUploadSubData(gl, type, i, start);

		Liar::Int colorOffset = m_color->GetStride();
		size_t colorOffsize = normalOffsize + m_normal->GetStride();

		gl.BufferSubData(type, colorOffsize, colorOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return normalOffsize;
	}

	size_t RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// normal
		size_t normalOffisze = Liar::RawVertexBuffersPositonNormal::VertexAttrbSubPointer(gl, stride);
		// color
		size_t colorOffisze = normalOffisze + m_normal->GetStride();
		Liar::Int colorFormat = m_color->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, colorFormat, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}
