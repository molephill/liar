#pragma once

#include "ISubVertexBuffers.h"

namespace Liar
{
	/**
	* 具体数据
	*/

	/**
	* vector2
	*/
	class SubVector2VertexBuffer :public Liar::ISubVertexBuffers
	{
	public:
		SubVector2VertexBuffer();
		virtual ~SubVector2VertexBuffer();

	protected:
		Liar::Vector2** m_buffers;
		Liar::Int m_numberBuffers;

	public:
		virtual Liar::Int GetStride() const;
		virtual Liar::Int GetFormat() const;

		virtual void AddVertexBuffer(void*);
		virtual void SetVertexBuffer(Liar::Int, void*);
		virtual void SetVertexBufferLen(Liar::Int);
		virtual void* GetVertexBuffer(Liar::Int) const;
	};

	/**
	* vector3
	*/
	class SubVector3VertexBuffer :public Liar::ISubVertexBuffers
	{
	public:
		SubVector3VertexBuffer();
		virtual ~SubVector3VertexBuffer();

	protected:
		Liar::Vector3** m_buffers;
		Liar::Int m_numberBuffers;

	public:
		virtual Liar::Int GetStride() const;
		virtual Liar::Int GetFormat() const;

		virtual void AddVertexBuffer(void*);
		virtual void SetVertexBuffer(Liar::Int, void*);
		virtual void SetVertexBufferLen(Liar::Int);
		virtual void* GetVertexBuffer(Liar::Int) const;
	};

	/**
	* Vector4
	*/
	class SubVector4VertexBuffer :public Liar::ISubVertexBuffers
	{
	public:
		SubVector4VertexBuffer();
		virtual ~SubVector4VertexBuffer();

	protected:
		Liar::Vector4** m_buffers;
		Liar::Int m_numberBuffers;

	public:
		virtual Liar::Int GetStride() const;
		virtual Liar::Int GetFormat() const;

		virtual void AddVertexBuffer(void*);
		virtual void SetVertexBuffer(Liar::Int, void*);
		virtual void SetVertexBufferLen(Liar::Int);
		virtual void* GetVertexBuffer(Liar::Int) const;
	};

	/**
	* Quat
	*/
	class SubQuatVertexBuffer :public Liar::ISubVertexBuffers
	{
	public:
		SubQuatVertexBuffer();
		virtual ~SubQuatVertexBuffer();

	protected:
		Liar::Quaternion** m_buffers;
		Liar::Int m_numberBuffers;

	public:
		virtual Liar::Int GetStride() const;
		virtual Liar::Int GetFormat() const;

		virtual void AddVertexBuffer(void*);
		virtual void SetVertexBuffer(Liar::Int, void*);
		virtual void SetVertexBufferLen(Liar::Int);
		virtual void* GetVertexBuffer(Liar::Int) const;
	};

}
