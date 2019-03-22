#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class RawVertexBuffersPositonColor:public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositonColor(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonColor();

	protected:
		Liar::SubVector3VertexBuffer* m_color;

	protected:
		// ����color��Ϣ
		virtual void AddColorVertexBuffer(Liar::IHeapOperator*);
		// ����color��Ϣ
		virtual void SetColorVertexBuffer(Liar::Int, Liar::IHeapOperator*);
		// ����color����
		virtual void SetColorVertexBufferLen(Liar::Int);
		// ���color��Ϣ
		virtual void* GetColorVertexBuffer(size_t) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		// ���� buffer ��Ϣ
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::IHeapOperator*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::IHeapOperator*);

		// ��֪ vertexBuffer ����
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// ȡ�� buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		// ����ύָ������������Ϣ
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		virtual Liar::Int GetStride() const;
	};
}