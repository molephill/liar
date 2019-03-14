#include <core/graphics/RawVertexBuffersPositonNormalColor.h>

namespace Liar
{
	VertexPositionNormalColorKey::VertexPositionNormalColorKey() :
		Liar::VertexPositionKey(), 
		m_normalIndex(0), m_colorIndex(0)
	{}

	Liar::Boolen VertexPositionNormalColorKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) &&
			m_colorIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) &&
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionNormalColorKey::Clone() const
	{
		Liar::VertexPositionNormalColorKey* tmp = new Liar::VertexPositionNormalColorKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, m_colorIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_normalIndex);
		return tmp;
	}

	void VertexPositionNormalColorKey::PrintData()
	{
		std::cout << m_positonIndex << "," << m_normalIndex << "," << m_colorIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositonNormalColor::RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normal(new Liar::SubVector3VertexBuffer()),
		m_color(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositonNormalColor::~RawVertexBuffersPositonNormalColor()
	{
		delete m_normal;
		m_normal = nullptr;

		delete m_color;
		m_color = nullptr;
	}

	// 增加normal信息
	void RawVertexBuffersPositonNormalColor::AddNormalVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_normal->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPositonNormalColor::AddNormalVertexBuffer(const Liar::Vector3& normal)
	{
		AddNormalVertexBuffer(normal.x, normal.y, normal.z);
	}

	// 设置normal信息
	void RawVertexBuffersPositonNormalColor::SetNormalVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z)
	{
		SetNormalVertexBuffer(index, new Liar::Vector3(x, y, z));
	}

	void RawVertexBuffersPositonNormalColor::SetNormalVertexBuffer(size_t index, Liar::Vector3* normal)
	{
		m_normal->SetVertexBuffer(index, normal);
	}

	// 设置normal长度
	void RawVertexBuffersPositonNormalColor::SetNormalVertexBufferLen(Liar::Int len)
	{
		m_normal->SetVertexBufferLen(len);
	}

	// 获得normal信息
	void* RawVertexBuffersPositonNormalColor::GetNormalVertexBuffer(size_t index) const
	{
		return m_normal->GetVertexBuffer(index);
	}

	// 增加color信息
	void RawVertexBuffersPositonNormalColor::AddColorVertexBuffer(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number a)
	{
		m_color->AddVertexBuffer(r, g, b, a);
	}

	void RawVertexBuffersPositonNormalColor::AddColorVertexBuffer(const Liar::Vector3& color)
	{
		AddColorVertexBuffer(color.x, color.y, color.z);
	}

	// 设置color信息
	void RawVertexBuffersPositonNormalColor::SetColorVertexBuffer(size_t index, Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number)
	{
		SetColorVertexBuffer(index, new Liar::Vector3(r, g, b));
	}

	void RawVertexBuffersPositonNormalColor::SetColorVertexBuffer(size_t index, Liar::Vector3* color)
	{
		m_color->SetVertexBuffer(index, (void*)color);
	}

	// 设置color长度
	void RawVertexBuffersPositonNormalColor::SetColorVertexBufferLen(Liar::Int len)
	{
		m_color->SetVertexBufferLen(len);
	}

	// 获得color信息
	void* RawVertexBuffersPositonNormalColor::GetColorVertexBuffer(size_t index) const
	{
		return m_color->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositonNormalColor::GetStride() const
	{
		return  m_normal->GetStride() + m_position->GetStride() + m_color->GetStride();
	}

	size_t RawVertexBuffersPositonNormalColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetStride();
		Liar::Int normalOffset = m_normal->GetStride();
		Liar::Int colorOffset = m_color->GetStride();

		size_t normalOffsize = positionOffsize + positionOffset;
		size_t colorOffsize = normalOffsize + colorOffset;

		gl.BufferSubData(type, normalOffsize, normalOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
		gl.BufferSubData(type, colorOffsize, colorOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));

		return normalOffsize;
	}

	size_t RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// normal
		size_t normalOffisze = positionOffsize + m_position->GetStride();
		Liar::Int normalFormat = m_normal->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, normalFormat, GL_FLOAT, GL_FALSE, stride, (void*)normalOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);
		// color
		size_t colorOffisze = normalOffisze + m_normal->GetStride();
		Liar::Int colorFormat = m_color->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, colorFormat, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}
