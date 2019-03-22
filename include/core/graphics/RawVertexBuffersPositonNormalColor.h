#pragma once

#include "RawVertexBuffersPositonNormal.h"

namespace Liar
{
	/*
	* ��������
	*/
	class RawVertexBuffersPositonNormalColor:public RawVertexBuffersPositonNormal
	{
	public:
		RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNormalColor();

	protected:
		Liar::SubVector3VertexBuffer* m_color;

	protected:
		// ����color��Ϣ
		virtual void AddColorVertexBuffer(void*);
		// ����color��Ϣ
		virtual void SetColorVertexBuffer(Liar::Int, void*);
		// ����color����
		virtual void SetColorVertexBufferLen(Liar::Int);
		// ���color��Ϣ
		virtual void* GetColorVertexBuffer(size_t) const;

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