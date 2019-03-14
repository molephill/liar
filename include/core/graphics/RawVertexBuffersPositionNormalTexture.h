#pragma once

#include "RawVertexBuffersPositonNormal.h"
#include "RawVertexBuffersPostionTexture.h"

namespace Liar
{
	class VertexPositionNormalTextureKey :public Liar::VertexPositionKey
	{
	public:
		VertexPositionNormalTextureKey();
		virtual ~VertexPositionNormalTextureKey() {};

	protected:
		Liar::Uint m_normalIndex;
		virtual void SetNormalIndex(Liar::Uint val) { m_normalIndex = val; };
		virtual Liar::Uint GetNormalIndex() const { return m_normalIndex; };
		Liar::Uint m_texCoordIndex;
		virtual void SetTexCoordIndex(Liar::Uint val) { m_texCoordIndex = val; };
		virtual Liar::Uint GetTexCoordIndex() const { return m_texCoordIndex; };

	public:
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPositionNormalTexture :public Liar::RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTexture();

	protected:
		Liar::SubVector3VertexBuffer* m_normal;
		Liar::SubVector2VertexBuffer* m_texCoord;

	protected:
		// 增加normal信息
		virtual void AddNormalVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void AddNormalVertexBuffer(const Liar::Vector3&);
		// 设置normal信息
		virtual void SetNormalVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void SetNormalVertexBuffer(size_t, Liar::Vector3*);
		// 设置normal长度
		virtual void SetNormalVertexBufferLen(Liar::Int);
		// 获得normal信息
		virtual void* GetNormalVertexBuffer(size_t) const;

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