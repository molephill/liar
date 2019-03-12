#pragma once

#include "RawVertexBuffersPositonColor.h"
#include "RawVertexBuffersPositonNormal.h"

namespace Liar
{
	class VertexPositionNormalColorKey :virtual public Liar::VertexPositionNormalKey, virtual public Liar::VertexPositionColorKey
	{
	public:
		VertexPositionNormalColorKey();
		virtual ~VertexPositionNormalColorKey() {};

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint);
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const;
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	/*
	* 具体数据
	*/
	class RawVertexBuffersPositonNormalColor:virtual public Liar::RawVertexBuffersPositonNormal, virtual public Liar::RawVertexBuffersPositonColor
	{
	public:
		RawVertexBuffersPositonNormalColor(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		~RawVertexBuffersPositonNormalColor();

	protected:
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