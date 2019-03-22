#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class RawVertexBuffersPositonNormal :public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositonNormal(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNormal();

	protected:
		Liar::SubVector3VertexBuffer* m_normal;

	protected:
		// 增加normal信息
		virtual void AddNormalVertexBuffer(void*);
		// 设置normal信息
		virtual void SetNormalVertexBuffer(Liar::Int, void*);
		// 设置normal长度
		virtual void SetNormalVertexBufferLen(Liar::Int);
		// 获得normal信息
		virtual void* GetNormalVertexBuffer(size_t) const;

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

		// 获得提交指定顶点属性信息
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		virtual Liar::Int GetSize() const;
	};
}