#pragma once

#include "RawVertexBuffersPositionNormal.h"

namespace Liar
{
	class RawVertexBuffersPositionNormalTexture :public Liar::RawVertexBuffersPositionNormal
	{
	public:
		RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

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
	};
}