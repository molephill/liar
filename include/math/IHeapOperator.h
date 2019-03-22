#pragma once

#include <LiarType.h>

namespace Liar
{
	struct IHeapOperator
	{
		/*IHeapOperator() {};
		virtual ~IHeapOperator() {};*/
	};

	class IFloatHeapOperator:public Liar::IHeapOperator
	{
	public:
		IFloatHeapOperator() :Liar::IHeapOperator() {};
		virtual ~IFloatHeapOperator() {};

		virtual bool operator==(const IFloatHeapOperator&) const = 0;
		virtual Liar::Number operator[](size_t) const = 0;
		virtual Liar::Number& operator[](size_t) = 0;
	};

	class IntHeapOperator:public Liar::IHeapOperator
	{
	public:
		IntHeapOperator(int len) :
			Liar::IHeapOperator(),
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
}