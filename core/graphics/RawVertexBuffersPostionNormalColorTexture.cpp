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

	// ���� buffer ��Ϣ
	void RawVertexBuffersPostionNormalColorTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPositonNormalColor::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPostionNormalColorTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositonNormalColor::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPostionNormalColorTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPositonNormalColor::SetSubVertexBufferLen(attr, len);
	}

	// ȡ�� buffer
	void* RawVertexBuffersPostionNormalColorTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return m_texCoord->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPositonNormalColor::GetSubVertexBuffer(attr, index);
	}

	Liar::Int RawVertexBuffersPostionNormalColorTexture::GetSize() const
	{
		return Liar::RawVertexBuffersPosition::GetSize() + m_normal->GetSize() + m_color->GetSize() + m_texCoord->GetSize();
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

	size_t RawVertexBuffersPostionNormalColorTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPositonNormalColor::LoopUploadSubData(gl, type, i, start);
		return m_texCoord->UploadData(gl, type, offset,
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
	}

	size_t RawVertexBuffersPostionNormalColorTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPositonNormalColor::VertexAttrbSubPointer(gl, stride);
		return m_texCoord->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, gl, stride, offset);
	}
}
