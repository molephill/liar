#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>
#include <core/render/RenderState.h>

namespace Liar
{
	/**
	* =============================== 动态int类型 ============================
	*/
	class IntHeapOperator
	{
	public:
		IntHeapOperator(int len) :
			m_buffer(new Liar::Int[len]), m_numBuffer(len)
		{};
		IntHeapOperator(Liar::Int x, Liar::Int y, Liar::Int z) :
			m_buffer(new Liar::Int[3]), m_numBuffer(3)
		{
			m_buffer[0] = x; m_buffer[1] = y; m_buffer[2] = z;
		};

		~IntHeapOperator() { delete[] m_buffer; };

	protected:
		Liar::Int* m_buffer;
		Liar::Int m_numBuffer;

	public:
		bool operator==(const IntHeapOperator& rhs) const
		{
			return Equal(rhs);
		};

		bool Equal(const IntHeapOperator& rhs) const
		{
			if (rhs.m_numBuffer != m_numBuffer) return false;
			for (int i = 0; i < m_numBuffer; ++i)
			{
				if (rhs[i] != m_buffer[i]) return false;
			}
			return true;
		}

		Liar::Int operator[](size_t index) const
		{
			return m_buffer[index];
		};

		Liar::Int& operator[](size_t index)
		{
			return m_buffer[index];
		}

		Liar::Int GetSize() const
		{
			return Liar::VertexElementSize::ELEMENT_SIZE_INT * m_numBuffer;
		}

		Liar::Int GetNumberBuffer() const
		{
			return m_numBuffer;
		}

		friend std::ostream& operator<<(std::ostream&, const Liar::IntHeapOperator&);
	};

	/**
	* =============================== 动态float类型 ============================
	*/
	inline std::ostream& operator<<(std::ostream& os, const IntHeapOperator& rhs)
	{
		os << "num: " << rhs.m_numBuffer;
		for (Liar::Int i = 0; i < rhs.m_numBuffer; ++i) os << "i: " << i << " val:" << rhs[i];
		return os;
	};

	class FloatHeapOperator
	{
	public:
		FloatHeapOperator(int len) :
			m_buffer(new Liar::Number[len]), m_numBuffer(len)
		{};
		FloatHeapOperator(Liar::Number x, Liar::Number y, Liar::Number z) :
			m_buffer(new Liar::Number[3]), m_numBuffer(3)
		{
			m_buffer[0] = x; m_buffer[1] = y; m_buffer[2] = z;
		};

		~FloatHeapOperator() { delete[] m_buffer; };

	protected:
		Liar::Number* m_buffer;
		Liar::Int m_numBuffer;

	public:
		bool operator==(const FloatHeapOperator& rhs) const
		{
			return Equal(rhs);
		};

		bool Equal(const FloatHeapOperator& rhs) const
		{
			if (rhs.m_numBuffer != m_numBuffer) return false;
			for (int i = 0; i < m_numBuffer; ++i)
			{
				if (rhs[i] != m_buffer[i]) return false;
			}
			return true;
		}

		Liar::Number operator[](size_t index) const
		{
			return m_buffer[index];
		};

		Liar::Number& operator[](size_t index)
		{
			return m_buffer[index];
		}

		Liar::Int GetSize() const
		{
			return Liar::VertexElementSize::ELEMENT_SIZE_FLOAT * m_numBuffer;
		}

		Liar::Int GetNumberBuffer() const
		{
			return m_numBuffer;
		}

		friend std::ostream& operator<<(std::ostream&, const Liar::FloatHeapOperator&);
	};

	inline std::ostream& operator<<(std::ostream& os, const FloatHeapOperator& rhs)
	{
		os << "num: " << rhs.m_numBuffer;
		for (Liar::Int i = 0; i < rhs.m_numBuffer; ++i) os << "i: " << i << " val:" << rhs[i];
		return os;
	};

	/**
	* =============================== vertexBuffers接口 ============================
	*/
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
		virtual Liar::Int GetType() const { return GL_FLOAT; };

		virtual void AddVertexBuffer(void*) = 0;
		virtual void SetVertexBuffer(Liar::Int, void*) = 0;
		virtual void SetVertexBufferLen(Liar::Int) = 0;
		virtual void* GetVertexBuffer(Liar::Int) const = 0;
		virtual void ToString() = 0;

	public:
		size_t UploadData(Liar::StageContext&, GLenum, size_t, void*);
		size_t AttribPointer(Liar::VertexAttribPointer, Liar::StageContext&, size_t, size_t = 0);
	};
}
