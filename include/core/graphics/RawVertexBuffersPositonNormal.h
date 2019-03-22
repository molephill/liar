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
		// ����normal��Ϣ
		virtual void AddNormalVertexBuffer(void*);
		// ����normal��Ϣ
		virtual void SetNormalVertexBuffer(Liar::Int, void*);
		// ����normal����
		virtual void SetNormalVertexBufferLen(Liar::Int);
		// ���normal��Ϣ
		virtual void* GetNormalVertexBuffer(size_t) const;

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

		// ����ύָ������������Ϣ
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		virtual Liar::Int GetSize() const;
	};
}