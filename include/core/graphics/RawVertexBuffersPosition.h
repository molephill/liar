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
	public:

		// ���� buffer ��Ϣ
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, void*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, void*);

		// ��֪ vertexBuffer ����
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// ȡ�� buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		virtual Liar::Int GetSize() const;
	};
}
