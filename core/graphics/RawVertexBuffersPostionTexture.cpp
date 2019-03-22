#include <core/graphics/RawVertexBuffersPostionTexture.h>

namespace Liar
{
	/*
	* ��������
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

	// ����texcoord��Ϣ
	void RawVertexBuffersPostionTexture::AddTexCoordVertexBuffer(void* data)
	{
		m_texCoord->AddVertexBuffer(data);
	}

	// ����texcoord��Ϣ
	void RawVertexBuffersPostionTexture::SetTexCoordVertexBuffer(Liar::Int index, void* data)
	{
		m_texCoord->SetVertexBuffer(index, data);
	}

	// ����texcoord����
	void RawVertexBuffersPostionTexture::SetTexCoordVertexBufferLen(Liar::Int len)
	{
		m_texCoord->SetVertexBufferLen(len);
	}

	// ���texcoord��Ϣ
	void* RawVertexBuffersPostionTexture::GetTexCoordVertexBuffer(Liar::Int index) const
	{
		return m_texCoord->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPostionTexture::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_texCoord->GetSize();
	}

	// ���� buffer ��Ϣ
	void RawVertexBuffersPostionTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) AddTexCoordVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPostionTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) SetTexCoordVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPostionTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) SetTexCoordVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPostionTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return GetTexCoordVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	// ����ύָ������������Ϣ
	void* RawVertexBuffersPostionTexture::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE)
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

	size_t RawVertexBuffersPostionTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int texCoordOffset = m_texCoord->GetSize();
		size_t texCoordOffsize = positionOffsize + m_position->GetSize();

		gl.BufferSubData(type, texCoordOffsize, texCoordOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		return texCoordOffsize;
	}

	size_t RawVertexBuffersPostionTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positionOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// texCoord
		size_t texCoordOffisze = positionOffsize + m_position->GetSize();
		Liar::Int texCoordFormat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFormat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffisze);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		return texCoordOffisze;
	}
}
