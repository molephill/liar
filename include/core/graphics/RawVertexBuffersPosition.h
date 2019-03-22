#pragma once

#include "IRawVertexBuffers.h"
#include "SubVertexBuffers.h"

#include <core/render/RenderState.h>
#include <math/Vector3.h>

namespace Liar
{
	class RawVertexBuffersPosition :public Liar::IRawVertexBuffers
	{
	public:
		RawVertexBuffersPosition(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPosition();

	protected:
		Liar::SubVector3VertexBuffer* m_position;

	protected:
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

		void AddPositionVertexBuffer(Liar::IHeapOperator*);
		void SetPositionVertexBuffer(Liar::Int, Liar::IHeapOperator*);
		void SetPositionVertexBufferLen(Liar::Int);
		void* GetPostionVertexBuffer(Liar::Int) const;

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
		virtual void VertexAttrbPointer();
	};
}
