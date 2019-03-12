#include <core/graphics/RawVertexBuffersPositonNormalColor.h>

namespace Liar
{
	VertexPositionNormalColorKey::VertexPositionNormalColorKey() :
		Liar::VertexPositionNormalKey(),
		Liar::VertexPositionColorKey()
	{}

	void VertexPositionNormalColorKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_colorIndex = index;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normalIndex = index;
			break;
		default:
			Liar::VertexPositionKey::SetVertexIndex(attr, index);
			break;
		}
	}

	Liar::Uint VertexPositionNormalColorKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			return m_colorIndex;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normalIndex;
		default:
			return Liar::VertexPositionKey::GetVertexIndex(attr);
		}
	}

	Liar::Boolen VertexPositionNormalColorKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return (Liar::VertexPositionNormalKey::operator==(rhs)) && (Liar::VertexPositionColorKey::operator==(rhs));
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
		Liar::VertexPositionKey::PrintData();
		std::cout << "," << m_normalIndex << "," << m_colorIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPositonNormalColor::RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositonNormal(type),
		Liar::RawVertexBuffersPositonColor(type)
	{
	}


	RawVertexBuffersPositonNormalColor::~RawVertexBuffersPositonNormalColor()
	{
	}

	void RawVertexBuffersPositonNormalColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			AddColorVertex(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			AddNormalVertex(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, x, y, z, w);
			break;
		}
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_numberColors = len;
			m_colors = (Liar::Vector3**)realloc(m_colors, sizeof(Liar::Vector3*)*m_numberColors);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_numberNormals = len;
			m_normals = (Liar::Vector3**)realloc(m_normals, sizeof(Liar::Vector3*)*m_numberNormals);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
			break;
		}
	}

	void RawVertexBuffersPositonNormalColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			m_colors[index] = new Liar::Vector3(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normals[index] = new Liar::Vector3(x, y, z);
			break;
		default:
			Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, x, y, z);
			break;
		}
	}

	void* RawVertexBuffersPositonNormalColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			return m_colors[index];
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return m_normals[index];
		default:
			return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
		}
	}

	Liar::Int RawVertexBuffersPositonNormalColor::GetStride() const
	{
		return  Liar::RawVertexBuffersPositonNormal::GetStride() + Liar::RawVertexBuffersPositonColor::GetStride() - Liar::RawVertexBuffersPosition::GetStride();
	}

	size_t RawVertexBuffersPositonNormalColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		size_t normalOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
		size_t colorOffsize = normalOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;

		gl.BufferSubData(type, normalOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
		gl.BufferSubData(type, colorOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
		return colorOffsize;
	}

	size_t RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);

		size_t normalOffsize = positionOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);

		size_t colorOffsize = normalOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)colorOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);

		return colorOffsize;
	}
}
