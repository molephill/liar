#include <core/graphics/RawVertexBuffersPostionNormalColorTexture.h>

namespace Liar
{

	/*
	* ��������
	*/
	RawVertexBuffersPostionNormalColorTexture::RawVertexBuffersPostionNormalColorTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositonNormalColor(type),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}


	RawVertexBuffersPostionNormalColorTexture::~RawVertexBuffersPostionNormalColorTexture()
	{
		delete m_texCoord;
		m_texCoord = nullptr;
	}

	// ����texcoord��Ϣ
	void RawVertexBuffersPostionNormalColorTexture::AddTexCoordVertexBuffer(Liar::IHeapOperator* data)
	{
		m_texCoord->AddVertexBuffer(data);
	}

	// ����texcoord��Ϣ
	void RawVertexBuffersPostionNormalColorTexture::SetTexCoordVertexBuffer(Liar::Int index, Liar::IHeapOperator* data)
	{
		m_texCoord->SetVertexBuffer(index, data);
	}

	// ����texcoord����
	void RawVertexBuffersPostionNormalColorTexture::SetTexCoordVertexBufferLen(Liar::Int len)
	{
		m_texCoord->SetVertexBufferLen(len);
	}

	// ���texcoord��Ϣ
	void* RawVertexBuffersPostionNormalColorTexture::GetTexCoordVertexBuffer(Liar::Int index) const
	{
		return m_texCoord->GetVertexBuffer(index);
	}

	// ���� buffer ��Ϣ
	void RawVertexBuffersPostionNormalColorTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) AddTexCoordVertexBuffer(data);
		else Liar::RawVertexBuffersPositonNormalColor::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPostionNormalColorTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) SetTexCoordVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositonNormalColor::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPostionNormalColorTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) SetTexCoordVertexBufferLen(len);
		else Liar::RawVertexBuffersPositonNormalColor::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPostionNormalColorTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return GetTexCoordVertexBuffer(index);
		else return Liar::RawVertexBuffersPositonNormalColor::GetSubVertexBuffer(attr, index);
	}

	// ����ύָ������������Ϣ
	void* RawVertexBuffersPostionNormalColorTexture::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return Liar::RawVertexBuffersPositonNormalColor::GetUploadVertexBuffer(index, attr);
		}
	}

	Liar::Int RawVertexBuffersPostionNormalColorTexture::GetStride() const
	{
		return Liar::RawVertexBuffersPosition::GetStride() + m_normal->GetStride() + m_color->GetStride() + m_texCoord->GetStride();
	}

	size_t RawVertexBuffersPostionNormalColorTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t colorOffsize = Liar::RawVertexBuffersPositonNormalColor::LoopUploadSubData(gl, type, i, start);

		Liar::Int texCoordOffset = m_texCoord->GetStride();
		size_t texCoordOffsize = colorOffsize + m_color->GetStride();

		gl.BufferSubData(type, texCoordOffsize, texCoordOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		return texCoordOffsize;
	}

	size_t RawVertexBuffersPostionNormalColorTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t colorOffisze = Liar::RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(gl, stride);
		// texCoord
		size_t texCoordOffsize = colorOffisze + m_color->GetStride();
		Liar::Int texCoordFormat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFormat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		return texCoordOffsize;
	}
}
