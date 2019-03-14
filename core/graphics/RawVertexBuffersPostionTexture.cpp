#include <core/graphics/RawVertexBuffersPostionTexture.h>

namespace Liar
{
	VertexPositionTextureKey::VertexPositionTextureKey() :
		Liar::VertexPositionKey(),
		m_texCoordIndex(0)
	{}

	Liar::Boolen VertexPositionTextureKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_texCoordIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) && 
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionTextureKey::Clone() const
	{
		Liar::VertexPositionTextureKey* tmp = new Liar::VertexPositionTextureKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_texCoordIndex);
		return tmp;
	}

	void VertexPositionTextureKey::PrintData()
	{
		std::cout << m_positonIndex << "," << m_texCoordIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPostionTexture::RawVertexBuffersPostionTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}

	RawVertexBuffersPostionTexture::~RawVertexBuffersPostionTexture()
	{
		delete m_texCoord;
		m_texCoord = nullptr;
	}

	// 增加texcoord信息
	void RawVertexBuffersPostionTexture::AddTexCoordVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_texCoord->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPostionTexture::AddTexCoordVertexBuffer(const Liar::Vector2& tex)
	{
		AddTexCoordVertexBuffer(tex.x, tex.y);
	}

	// 设置texcoord信息
	void RawVertexBuffersPostionTexture::SetTexCoordVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number)
	{
		SetTexCoordVertexBuffer(index, new Liar::Vector2(x, y));
	}

	void RawVertexBuffersPostionTexture::SetTexCoordVertexBuffer(size_t index, Liar::Vector2* tex)
	{
		m_texCoord->SetVertexBuffer(index, tex);
	}

	// 设置texcoord长度
	void RawVertexBuffersPostionTexture::SetTexCoordVertexBufferLen(Liar::Int len)
	{
		m_texCoord->SetVertexBufferLen(len);
	}

	// 获得texcoord信息
	void* RawVertexBuffersPostionTexture::GetTexCoordVertexBuffer(size_t index) const
	{
		return m_texCoord->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPostionTexture::GetStride() const
	{
		return  m_position->GetStride() + m_texCoord->GetStride();
	}

	size_t RawVertexBuffersPostionTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positionOffset = m_position->GetStride();
		Liar::Int texCoordOffset = m_texCoord->GetStride();

		size_t texCoordOffsize = positionOffsize + positionOffset;
		gl.BufferSubData(type, texCoordOffsize, texCoordOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		return texCoordOffsize;
	}

	size_t RawVertexBuffersPostionTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// texCoord
		size_t texCoordOffisze = positionOffsize + m_position->GetStride();
		Liar::Int texCoordFormat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFormat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		return texCoordOffisze;
	}
}
