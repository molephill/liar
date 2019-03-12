#include <core/graphics/RawVertexBuffersPositonColor.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionColorKey::VertexPositionColorKey() :
		Liar::VertexPositionKey(),
		m_colorIndex(0)
	{}

	void VertexPositionColorKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_colorIndex = index;
			break;
		default:
			Liar::VertexPositionKey::SetVertexIndex(attr, index);
			break;
		}
	}

	Liar::Uint VertexPositionColorKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			return m_colorIndex;
		default:
			return Liar::VertexPositionKey::GetVertexIndex(attr);
		}
	}

	Liar::Boolen VertexPositionColorKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return	m_colorIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) && Liar::VertexPositionKey::operator==(rhs);
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
		Liar::VertexPositionKey::PrintData();
		std::cout << "," << m_colorIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositonColor::RawVertexBuffersPositonColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_colors(nullptr), m_numberColors(0)
	{
	}


	RawVertexBuffersPositonColor::~RawVertexBuffersPositonColor()
	{
		if (m_colors)
		{
			for (size_t i = 0; i < m_numberColors; ++i)
			{
				delete m_colors[i];
				m_colors[i] = nullptr;
			}
			free(m_colors);
			m_colors = nullptr;
		}
	}

	void RawVertexBuffersPositonColor::AddColorVertex(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		void* buffer = GetVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, (void**)m_colors, m_numberColors, x, y, z);
		Liar::Vector3* color = static_cast<Liar::Vector3*>(buffer);
		if (!color)
		{
			++m_numberColors;
			size_t blockSize = sizeof(Liar::Vector3*)*m_numberColors;
			if (!m_colors) m_colors = (Liar::Vector3**)malloc(blockSize);
			else m_colors = (Liar::Vector3**)realloc(m_colors, blockSize);
			color = new Liar::Vector3(x, y, z);
			m_colors[m_numberColors - 1] = color;
		}
	}

	void RawVertexBuffersPositonColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			AddColorVertex(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, x, y, z, w);
			break;
		}
	}

	void RawVertexBuffersPositonColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_numberColors = len;
			m_colors = (Liar::Vector3**)realloc(m_colors, sizeof(Liar::Vector3*)*m_numberColors);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
			break;
		}
	}

	void RawVertexBuffersPositonColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_colors[index] = new Liar::Vector3(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, x, y, z);
			break;
		}
	}

	void* RawVertexBuffersPositonColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			return m_colors[index];
		default:
			return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
		}
	}

	Liar::Int RawVertexBuffersPositonColor::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
	}

	size_t RawVertexBuffersPositonColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		size_t colorOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
		gl.BufferSubData(type, colorOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return colorOffsize;
	}

	size_t RawVertexBuffersPositonColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		size_t colorOffisze = positionOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}