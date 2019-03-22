#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	class IntHeapOperator
	{
	public:
		IntHeapOperator(int len) :
			m_buffer(new Liar::Int[len]), m_numBuffer(len)
		{};

		virtual ~IntHeapOperator() { delete[] m_buffer; };

	protected:
		Liar::Int* m_buffer;
		Liar::Int m_numBuffer;

	public:
		bool operator==(const IntHeapOperator& rhs) const
		{
			if (rhs.m_numBuffer != m_numBuffer) return false;
			for (int i = 0; i < m_numBuffer; ++i)
			{
				if (rhs[i] != m_buffer[i]) return false;
			}
			return true;
		};

		Liar::Int operator[](size_t index) const
		{
			return m_buffer[index];
		};

		Liar::Int& operator[](size_t index)
		{
			return m_buffer[index];
		}
	};

	class ISubVertexBuffers
	{
	public:
		ISubVertexBuffers() {};
		virtual ~ISubVertexBuffers() {};

	protected:
		void* GetSubVertexBuffer(Liar::VertexFormatType, void**, size_t, void*);

	public:
		virtual Liar::Int GetSize() const = 0;
		virtual Liar::Int GetFormat() const = 0;

		virtual void AddVertexBuffer(void*) = 0;
		virtual void SetVertexBuffer(Liar::Int, void*) = 0;
		virtual void SetVertexBufferLen(Liar::Int) = 0;
		virtual void* GetVertexBuffer(Liar::Int) const = 0;
		virtual void ToString() = 0;
	};
}
