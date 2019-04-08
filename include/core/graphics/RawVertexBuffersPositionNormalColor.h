#pragma once

#include "RawVertexBuffersPositionNormal.h"

namespace Liar
{
	/*
	* 具体数据
	*/
	class RawVertexBuffersPositonNormalColor:public RawVertexBuffersPositionNormal
	{
	public:
		RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNormalColor();

	protected:
		Liar::SubVector3VertexBuffer* m_color;

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