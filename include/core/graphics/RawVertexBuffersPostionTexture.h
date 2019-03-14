#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionTextureKey :public Liar::VertexPositionKey
	{
	public:
		VertexPositionTextureKey();
		virtual ~VertexPositionTextureKey() {};

	protected:
		Liar::Uint m_texCoordIndex;
		virtual void SetTexCoordIndex(Liar::Uint val) { m_texCoordIndex = val; };

	public:
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	/*
	* 具体数据
	*/
	class RawVertexBuffersPostionTexture:public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPostionTexture(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPostionTexture();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;

	protected:
		// 增加texcoord信息
		virtual void AddTexCoordVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void AddTexCoordVertexBuffer(const Liar::Vector2&);
		// 设置texcoord信息
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Vector2*);
		// 设置texcoord长度
		virtual void SetTexCoordVertexBufferLen(Liar::Int);
		// 获得texcoord信息
		virtual void* GetTexCoordVertexBuffer(size_t) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual Liar::Int GetStride() const;
	};
}
