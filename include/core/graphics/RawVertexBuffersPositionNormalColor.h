#pragma once

#include "RawVertexBuffersPositionNormal.h"

namespace Liar
{
	/*
	* ��������
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
		// ���� buffer ��Ϣ
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, void*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, void*);

		// ��֪ vertexBuffer ����
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// ȡ�� buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		virtual Liar::Int GetSize() const;

		virtual void Print(std::ostream&) const;
	};
}