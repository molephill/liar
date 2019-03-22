#pragma once

#include "RawVertexBuffersPositonNormal.h"

namespace Liar
{
	/*
	* 具体数据
	*/
	class RawVertexBuffersPositonNormalColor:public RawVertexBuffersPositonNormal
	{
	public:
		RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNormalColor();

	protected:
		Liar::SubVector3VertexBuffer* m_color;

	protected:
		// 增加color信息
		virtual void AddColorVertexBuffer(void*);
		// 设置color信息
		virtual void SetColorVertexBuffer(Liar::Int, void*);
		// 设置color长度
		virtual void SetColorVertexBufferLen(Liar::Int);
		// 获得color信息
		virtual void* GetColorVertexBuffer(size_t) const;

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