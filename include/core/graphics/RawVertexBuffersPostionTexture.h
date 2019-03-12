#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionTextureKey :virtual public Liar::VertexPositionKey
	{
	public:
		VertexPositionTextureKey();
		virtual ~VertexPositionTextureKey() {};

	protected:
		Liar::Uint m_texIndex;

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
	class RawVertexBuffersPostionTexture:virtual public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPostionTexture(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		~RawVertexBuffersPostionTexture();

	protected:
		Liar::Vector3** m_colors;
		Liar::Uint m_numberColors;

	protected:
		virtual void AddTextureVertex(Liar::Number x, Liar::Number y, Liar::Number z);
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
