#include <core/graphics/RawVertexBuffersPostionNormalColorTexture.h>

namespace Liar
{
	VertexPositionNormalColorTextureKey::VertexPositionNormalColorTextureKey() :
		Liar::VertexPositionKey(),
		m_normalIndex(0), m_colorIndex(0), m_texCoordIndex(0)
	{}

	Liar::Boolen VertexPositionNormalColorTextureKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) &&
			m_colorIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) &&
			m_texCoordIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) &&
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionNormalColorTextureKey::Clone() const
	{
		Liar::VertexPositionNormalColorTextureKey* tmp = new Liar::VertexPositionNormalColorTextureKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, m_colorIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_normalIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_texCoordIndex);
		return tmp;
	}

	void VertexPositionNormalColorTextureKey::PrintData()
	{
		std::cout << m_positonIndex << "," << m_normalIndex << "," << m_colorIndex << "," << m_texCoordIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPostionNormalColorTexture::RawVertexBuffersPostionNormalColorTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normal(new Liar::SubVector3VertexBuffer()),
		m_color(new Liar::SubVector3VertexBuffer()),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}


	RawVertexBuffersPostionNormalColorTexture::~RawVertexBuffersPostionNormalColorTexture()
	{
		delete m_normal;
		m_normal = nullptr;

		delete m_color;
		m_color = nullptr;

		delete m_texCoord;
		m_texCoord = nullptr;
	}

	// 增加normal信息
	void RawVertexBuffersPostionNormalColorTexture::AddNormalVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_normal->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPostionNormalColorTexture::AddNormalVertexBuffer(const Liar::Vector3& normal)
	{
		AddNormalVertexBuffer(normal.x, normal.y, normal.z);
	}

	// 设置normal信息
	void RawVertexBuffersPostionNormalColorTexture::SetNormalVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z)
	{
		SetNormalVertexBuffer(index, new Liar::Vector3(x, y, z));
	}

	void RawVertexBuffersPostionNormalColorTexture::SetNormalVertexBuffer(size_t index, Liar::Vector3* normal)
	{
		m_normal->SetVertexBuffer(index, normal);
	}

	// 设置normal长度
	void RawVertexBuffersPostionNormalColorTexture::SetNormalVertexBufferLen(Liar::Int len)
	{
		m_normal->SetVertexBufferLen(len);
	}

	// 获得normal信息
	void* RawVertexBuffersPostionNormalColorTexture::GetNormalVertexBuffer(size_t index) const
	{
		return m_normal->GetVertexBuffer(index);
	}

	// 增加color信息
	void RawVertexBuffersPostionNormalColorTexture::AddColorVertexBuffer(Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number a)
	{
		m_color->AddVertexBuffer(r, g, b, a);
	}

	void RawVertexBuffersPostionNormalColorTexture::AddColorVertexBuffer(const Liar::Vector3& color)
	{
		AddColorVertexBuffer(color.x, color.y, color.z);
	}

	// 设置color信息
	void RawVertexBuffersPostionNormalColorTexture::SetColorVertexBuffer(size_t index, Liar::Number r, Liar::Number g, Liar::Number b, Liar::Number)
	{
		SetColorVertexBuffer(index, new Liar::Vector3(r, g, b));
	}

	void RawVertexBuffersPostionNormalColorTexture::SetColorVertexBuffer(size_t index, Liar::Vector3* color)
	{
		m_color->SetVertexBuffer(index, (void*)color);
	}

	// 设置color长度
	void RawVertexBuffersPostionNormalColorTexture::SetColorVertexBufferLen(Liar::Int len)
	{
		m_color->SetVertexBufferLen(len);
	}

	// 获得color信息
	void* RawVertexBuffersPostionNormalColorTexture::GetColorVertexBuffer(size_t index) const
	{
		return m_color->GetVertexBuffer(index);
	}

	// 增加texcoord信息
	void RawVertexBuffersPostionNormalColorTexture::AddTexCoordVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_texCoord->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPostionNormalColorTexture::AddTexCoordVertexBuffer(const Liar::Vector2& tex)
	{
		AddTexCoordVertexBuffer(tex.x, tex.y);
	}

	// 设置texcoord信息
	void RawVertexBuffersPostionNormalColorTexture::SetTexCoordVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number)
	{
		SetTexCoordVertexBuffer(index, new Liar::Vector2(x, y));
	}

	void RawVertexBuffersPostionNormalColorTexture::SetTexCoordVertexBuffer(size_t index, Liar::Vector2* tex)
	{
		m_texCoord->SetVertexBuffer(index, tex);
	}

	// 设置texcoord长度
	void RawVertexBuffersPostionNormalColorTexture::SetTexCoordVertexBufferLen(Liar::Int len)
	{
		m_texCoord->SetVertexBufferLen(len);
	}

	// 获得texcoord信息
	void* RawVertexBuffersPostionNormalColorTexture::GetTexCoordVertexBuffer(size_t index) const
	{
		return m_texCoord->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPostionNormalColorTexture::GetStride() const
	{
		return Liar::RawVertexBuffersPosition::GetStride() + m_normal->GetStride() + m_color->GetStride() + m_texCoord->GetStride();
	}

	size_t RawVertexBuffersPostionNormalColorTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetStride();
		Liar::Int normalOffset = m_normal->GetStride();
		Liar::Int colorOffset = m_color->GetStride();
		Liar::Int texCoordOffset = m_texCoord->GetStride();

		size_t normalOffsize = positionOffsize + positionOffset;
		size_t texCoordOffsize = normalOffsize + normalOffset;
		size_t colorOffsize = texCoordOffsize + texCoordOffset;

		gl.BufferSubData(type, normalOffsize, normalOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
		gl.BufferSubData(type, texCoordOffsize, texCoordOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		gl.BufferSubData(type, colorOffsize, colorOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));

		return colorOffsize;
	}

	size_t RawVertexBuffersPostionNormalColorTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// normal
		size_t normalOffsize = positionOffsize + m_position->GetStride();
		Liar::Int normalFormat = m_normal->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, normalFormat, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);
		// texCoord
		size_t texCoordOffsize = normalOffsize + m_normal->GetStride();
		Liar::Int texCoordFormat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFormat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		// color
		size_t colorOffisze = texCoordOffsize + m_texCoord->GetStride();
		Liar::Int colorFormat = m_color->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR, colorFormat, GL_FLOAT, GL_FALSE, stride, (void*)colorOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_COLOR);
		return colorOffisze;
	}
}
