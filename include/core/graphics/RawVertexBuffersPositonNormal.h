#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionNormalKey :virtual public Liar::VertexPositionKey
	{
	public:
		VertexPositionNormalKey();
		virtual ~VertexPositionNormalKey() {};

	protected:
		Liar::Uint m_normalIndex;

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint);
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const;
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPositonNormal :virtual public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositonNormal(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		~RawVertexBuffersPositonNormal();

	protected:
		Liar::Vector3** m_normals;
		Liar::Uint m_numberNormals;

	protected:
		virtual void AddNormalVertex(Liar::Number x, Liar::Number y, Liar::Number z);
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number);
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t);

		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f);

		virtual Liar::Int GetStride() const;
	};
}