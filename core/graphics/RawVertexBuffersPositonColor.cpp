#include <core/graphics/RawVertexBuffersPositonColor.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionColorKey::VertexPositionColorKey() :
		Liar::VertexPositionKey(),
		m_colorIndex(0)
	{}

	Liar::Boolen VertexPositionColorKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_colorIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) &&
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionColorKey::Clone() const
	{
		Liar::VertexPositionColorKey* tmp = new Liar::VertexPositionColorKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, m_colorIndex);
		return tmp;
	}

	void VertexPositionColorKey::PrintData()
	{
		std::cout << m_positonIndex << "," << m_colorIndex;
	}

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
	void RawVertexBuffersPositonColor::AddColorVertexBuffer(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number a)
	{
		m_color->AddVertexBuffer(r, g, b, a);
	}

	void RawVertexBuffersPositonColor::AddColorVertexBuffer(const Liar::Vector3& color)
	{
		AddColorVertexBuffer(color.x, color.y, color.z);
	}

	// 设置color信息
	void RawVertexBuffersPositonColor::SetColorVertexBuffer(size_t index, Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number)
	{
		SetColorVertexBuffer(index, new Liar::Vector3(r, g, b));
	}

	void RawVertexBuffersPositonColor::SetColorVertexBuffer(size_t index, Liar::Vector3* color)
	{
		m_color->SetVertexBuffer(index, (void*)color);
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

	Liar::Int RawVertexBuffersPositonColor::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + m_color->GetStride();
	}

	size_t RawVertexBuffersPositonColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetStride();
		Liar::Int colorOffset = m_color->GetStride();

		size_t colorOffsize = positionOffsize + positionOffset;
		gl.BufferSubData(type, colorOffsize, colorOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return colorOffsize;
	}

	size_t RawVertexBuffersPositonColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// color
		size_t colorOffisze = positionOffsize + m_position->GetStride();
		Liar::Int colorFormat = m_color->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, colorFormat, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}