#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	/*
	* ��������
	*/
	class RawVertexBuffersPostionTexture:public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPostionTexture(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPostionTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

	protected:
		// ����texcoord��Ϣ
		virtual void AddTexCoordVertexBuffer(void*);
		// ����texcoord��Ϣ
		virtual void SetTexCoordVertexBuffer(Liar::Int, void*);
		// ����texcoord����
		virtual void SetTexCoordVertexBufferLen(Liar::Int);
		// ���texcoord��Ϣ
		virtual void* GetTexCoordVertexBuffer(Liar::Int) const;

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
