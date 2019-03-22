#pragma once

#include "RawVertexBuffersPositonNormal.h"

namespace Liar
{
	class RawVertexBuffersPositionNormalTexture :public Liar::RawVertexBuffersPositonNormal
	{
	public:
		RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

	protected:
		// 增加texcoord信息
		virtual void AddTexCoordVertexBuffer(Liar::IHeapOperator*);
		// 设置texcoord信息
		virtual void SetTexCoordVertexBuffer(Liar::Int, Liar::IHeapOperator*);
		// 设置texcoord长度
		virtual void SetTexCoordVertexBufferLen(Liar::Int);
		// 获得texcoord信息
		virtual void* GetTexCoordVertexBuffer(Liar::Int) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		// 设置 buffer 信息
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::IHeapOperator*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::IHeapOperator*);

		// 已知 vertexBuffer 长度
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// 取得 buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		// 获得提交指定顶点属性信息
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		virtual Liar::Int GetStride() const;
	};
}