#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	/*
	* ��������
	*/
	class RawVertexBuffersPositionTexture:public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositionTexture(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

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

		// ����ύָ������������Ϣ
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		virtual Liar::Int GetSize() const;
	};
}
