#include <core/graphics/RawVertexBuffersPositonColor.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositonColor::RawVertexBuffersPositonColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_color(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositonColor::~RawVertexBuffersPositonColor()
	{
		delete m_color;
		m_color = nullptr;
	}

	// 增加color信息
	void RawVertexBuffersPositonColor::AddColorVertexBuffer(void* data)
	{
		m_color->AddVertexBuffer(data);
	}

	// 设置color信息
	void RawVertexBuffersPositonColor::SetColorVertexBuffer(Liar::Int index, void* data)
	{
		m_color->SetVertexBuffer(index, data);
	}

	// 设置color长度
	void RawVertexBuffersPositonColor::SetColorVertexBufferLen(Liar::Int len)
	{
		m_color->SetVertexBufferLen(len);
	}

	// 获得color信息
	void* RawVertexBuffersPositonColor::GetColorVertexBuffer(size_t index) const
	{
		return m_color->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositonColor::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_color->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositonColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) AddColorVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositonColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) SetColorVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositonColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) SetColorVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositonColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) return GetColorVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
	void* RawVertexBuffersPositonColor::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR)
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

	size_t RawVertexBuffersPositonColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetSize();
		Liar::Int colorOffset = m_color->GetSize();

		size_t colorOffsize = positionOffsize + positionOffset;
		gl.BufferSubData(type, colorOffsize, colorOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return colorOffsize;
	}

	size_t RawVertexBuffersPositonColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// color
		size_t colorOffisze = positionOffsize + m_position->GetSize();
		Liar::Int colorFormat = m_color->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, colorFormat, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}