#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <core/render/RenderState.h>
#include <math/Vector3.h>

namespace Liar
{
	class VertexPositionKey :public Liar::IVertexKey
	{
	public:
		VertexPositionKey();
		virtual ~VertexPositionKey() {};

	protected:
		Liar::Uint m_positonIndex;

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint);
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const;
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPosition :public Liar::IRawVertexBuffers
	{
	public:
		RawVertexBuffersPosition(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		~RawVertexBuffersPosition();

	protected:
		Liar::Vector3** m_positons;
		Liar::Uint m_numberPostions;

	protected:
		virtual void AddPositonVertex(Liar::Number x, Liar::Number y, Liar::Number z);
		virtual void UploadSubData(GLenum);
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number);
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t);

		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f);

		virtual Liar::Int GetStride() const;
		virtual void VertexAttrbPointer();

		virtual void PrintData();
	};
}
