
#include <core/graphics/RawVertexBuffersPositionNormalTexture.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositionNormalTexture::RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositionNormal(type),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}

	RawVertexBuffersPositionNormalTexture::~RawVertexBuffersPositionNormalTexture()
	{
		delete m_texCoord;
		m_texCoord = nullptr;
	}

	Liar::Int RawVertexBuffersPositionNormalTexture::GetSize() const
	{
		return  Liar::RawVertexBuffersPositionNormal::GetSize() + m_texCoord->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionNormalTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPositionNormal::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositionNormal::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPositionNormal::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionNormalTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return m_texCoord->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPositionNormal::GetSubVertexBuffer(attr, index);
	}

	size_t RawVertexBuffersPositionNormalTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPositionNormal::LoopUploadSubData(gl, type, i, start);
		return m_texCoord->UploadData(gl, type, offset, 
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
	}

	size_t RawVertexBuffersPositionNormalTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPositionNormal::VertexAttrbSubPointer(gl, stride);
		return m_texCoord->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, gl, stride, offset);
	}
}