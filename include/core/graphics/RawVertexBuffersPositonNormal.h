#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionNormalKey :public Liar::VertexPositionKey
	{
	public:
		VertexPositionNormalKey();
		virtual ~VertexPositionNormalKey() {};

	protected:
		Liar::Uint m_normalIndex;
		virtual void SetNormalIndex(Liar::Uint val) { m_normalIndex = val; };
		virtual Liar::Uint GetNormalIndex() const { return m_normalIndex; };

	public:
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPositonNormal :public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositonNormal(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNormal();

	protected:
		Liar::SubVector3VertexBuffer* m_normal;

	protected:
		// ����normal��Ϣ
		virtual void AddNormalVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void AddNormalVertexBuffer(const Liar::Vector3&);
		// ����normal��Ϣ
		virtual void SetNormalVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void SetNormalVertexBuffer(size_t, Liar::Vector3*);
		// ����normal����
		virtual void SetNormalVertexBufferLen(Liar::Int);
		// ���normal��Ϣ
		virtual void* GetNormalVertexBuffer(size_t) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual Liar::Int GetStride() const;
	};
}