#include <core/graphics/RawVertexBuffersPositionTexture.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositionTexture::RawVertexBuffersPositionTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}

	RawVertexBuffersPositionTexture::~RawVertexBuffersPositionTexture()
	{
		delete m_texCoord;
		m_texCoord = nullptr;
	}

	Liar::Int RawVertexBuffersPositionTexture::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_texCoord->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return m_texCoord->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	size_t RawVertexBuffersPositionTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		return m_texCoord->UploadData(gl, type, offset,
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
	}

	size_t RawVertexBuffersPositionTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		return m_texCoord->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, gl, stride, offset);
	}

	void RawVertexBuffersPositionTexture::Print(std::ostream& os) const
	{
		Liar::RawVertexBuffersPosition::Print(os);
		os << "\ntexCoord:\n";
		m_texCoord->Print(os);
	}
}
