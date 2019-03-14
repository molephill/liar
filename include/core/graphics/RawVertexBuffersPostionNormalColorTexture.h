#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionNormalColorTextureKey :public Liar::VertexPositionKey
	{
	public:
		VertexPositionNormalColorTextureKey();
		virtual ~VertexPositionNormalColorTextureKey() {};

	protected:
		Liar::Uint m_normalIndex;
		virtual void SetNormalIndex(Liar::Uint val) { m_normalIndex = val; };
		virtual Liar::Uint GetNormalIndex() const { return m_normalIndex; };
		Liar::Uint m_colorIndex;
		virtual void SetColorIndex(Liar::Uint val) { m_colorIndex = val; };
		virtual Liar::Uint GetColorIndex() const { return m_colorIndex; };
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
	class RawVertexBuffersPostionNormalColorTexture:public Liar::RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPostionNormalColorTexture(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPostionNormalColorTexture();

	protected:
		Liar::SubVector3VertexBuffer* m_normal;
		Liar::SubVector3VertexBuffer* m_color;
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

		// 增加color信息
		virtual void AddColorVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		virtual void AddColorVertexBuffer(const Liar::Vector3&);
		// 设置color信息
		virtual void SetColorVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		virtual void SetColorVertexBuffer(size_t, Liar::Vector3*);
		// 设置color长度
		virtual void SetColorVertexBufferLen(Liar::Int);
		// 获得color信息
		virtual void* GetColorVertexBuffer(size_t) const;

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
