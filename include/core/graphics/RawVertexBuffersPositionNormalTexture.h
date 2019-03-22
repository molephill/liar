#pragma once

#include "RawVertexBuffersPositonNormal.h"

namespace Liar
{
	class RawVertexBuffersPositionNormalTexture :public Liar::RawVertexBuffersPositonNormal
	{
	public:
		RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

	protected:
		// ����texcoord��Ϣ
		virtual void AddTexCoordVertexBuffer(Liar::IHeapOperator*);
		// ����texcoord��Ϣ
		virtual void SetTexCoordVertexBuffer(Liar::Int, Liar::IHeapOperator*);
		// ����texcoord����
		virtual void SetTexCoordVertexBufferLen(Liar::Int);
		// ���texcoord��Ϣ
		virtual void* GetTexCoordVertexBuffer(Liar::Int) const;

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