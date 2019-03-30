
#include <core/graphics/RawVertexBuffersPositionNormalTextureSkin.h>

namespace Liar
{
	RawVertexBuffersPositionNormalTextureSkin::RawVertexBuffersPositionNormalTextureSkin(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPositionNormalTexture(type),
		m_boneIndices(new Liar::SubIntVertexBuffer()),
		m_boneWeights(new Liar::SubFloatVertexBuffer())
	{
	}


	RawVertexBuffersPositionNormalTextureSkin::~RawVertexBuffersPositionNormalTextureSkin()
	{
		delete m_boneIndices;
		m_boneIndices = nullptr;
		delete m_boneWeights;
		m_boneWeights = nullptr;
	}

	Liar::Int RawVertexBuffersPositionNormalTextureSkin::GetSize() const
	{
		return  Liar::RawVertexBuffersPositionNormalTexture::GetSize() + m_boneIndices->GetSize() + m_boneWeights->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionNormalTextureSkin::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES) m_boneIndices->AddVertexBuffer(data);
		else if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS) m_boneWeights->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPositionNormalTexture::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionNormalTextureSkin::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES) m_boneIndices->SetVertexBuffer(index, data);
		else if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS) m_boneWeights->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPositionNormalTexture::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionNormalTextureSkin::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES) m_boneIndices->SetVertexBufferLen(len);
		else if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS) m_boneWeights->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPositionNormalTexture::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionNormalTextureSkin::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES) return m_boneIndices->GetVertexBuffer(index);
		else if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS) return m_boneWeights->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPositionNormalTexture::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
	void* RawVertexBuffersPositionNormalTextureSkin::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES || attr == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return Liar::RawVertexBuffersPositionNormal::GetUploadVertexBuffer(index, attr);
		}
	}

	size_t RawVertexBuffersPositionNormalTextureSkin::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPositionNormalTexture::LoopUploadSubData(gl, type, i, start);
		offset = m_boneIndices->UploadData(gl, type, offset,	GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES));
		return m_boneWeights->UploadData(gl, type, offset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS));
	}

	size_t RawVertexBuffersPositionNormalTextureSkin::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPositionNormalTexture::VertexAttrbSubPointer(gl, stride);
		offset = m_boneIndices->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_BONE_INDICES, gl, stride, offset);
		return m_boneWeights->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_BONE_WEIGHTS, gl, stride, offset);
	}
}
