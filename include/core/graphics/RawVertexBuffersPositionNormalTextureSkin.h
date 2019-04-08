#pragma once

#include "RawVertexBuffersPositionNormalTexture.h"

namespace Liar
{
	class RawVertexBuffersPositionNormalTextureSkin:public Liar::RawVertexBuffersPositionNormalTexture
	{
	public:
		RawVertexBuffersPositionNormalTextureSkin(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTextureSkin();

	protected:
		Liar::SubVector4VertexBuffer* m_boneIndices;
		Liar::SubVector4VertexBuffer* m_boneWeights;

	protected:
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		// 设置 buffer 信息
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, void*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, void*);

		// 已知 vertexBuffer 长度
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// 取得 buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		virtual Liar::Int GetSize() const;

		virtual void Print(std::ostream&) const;
	};
}