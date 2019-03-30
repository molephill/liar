
#include <core/graphics/RawVertexBuffersPositionNormalTexture.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositionNormalTexture::RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositonNormal(type),
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
		return  Liar::RawVertexBuffersPositonNormal::GetSize() + m_texCoord->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionNormalTexture::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPositonNormal::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionNormalTexture::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) m_texCoord->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPositonNormal::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionNormalTexture::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) return m_texCoord->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPositonNormal::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
	void* RawVertexBuffersPositionNormalTexture::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return Liar::RawVertexBuffersPositonNormal::GetUploadVertexBuffer(index, attr);
		}
	}

	size_t RawVertexBuffersPositionNormalTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t normalOffset = Liar::RawVertexBuffersPositonNormal::LoopUploadSubData(gl, type, i, start);

		Liar::Int texCoordSize = m_texCoord->GetSize();
		size_t texCoordOffset = normalOffset + m_normal->GetSize();
		void* texCoord = GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE);
		gl.BufferSubData(type, texCoordOffset, texCoordSize, texCoord);
		return texCoordOffset;
	}

	size_t RawVertexBuffersPositionNormalTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t normalOffset = Liar::RawVertexBuffersPositonNormal::VertexAttrbSubPointer(gl, stride);
		// texCoord
		size_t texCoordOffset = normalOffset + m_normal->GetSize();
		Liar::Int texCoordFromat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFromat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffset);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		return texCoordOffset;
	}
}