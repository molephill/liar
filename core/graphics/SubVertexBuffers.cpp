#include <core/graphics/SubVertexBuffers.h>

namespace Liar
{
	/**
	* 具体数据
	*/
	SubVector2VertexBuffer::SubVector2VertexBuffer():
		Liar::ISubVertexBuffers(),
		m_buffers(nullptr), m_numberBuffers(0)
	{}

	SubVector2VertexBuffer::~SubVector2VertexBuffer()
	{
		if (m_buffers)
		{
			for (Liar::Int i = 0; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
			free(m_buffers);
			m_buffers = nullptr;
		}
	}

	Liar::Int SubVector2VertexBuffer::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
	}

	Liar::Int SubVector2VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR2;
	}

	void SubVector2VertexBuffer::AddVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2, (void**)m_buffers, m_numberBuffers, x, y, z, w);
		Liar::Vector2* color = static_cast<Liar::Vector2*>(buffer);
		if (!color)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			color = new Liar::Vector2(x, y);
			m_buffers[m_numberBuffers - 1] = color;
		}
	}

	void SubVector2VertexBuffer::AddVertexBuffer(void* c)
	{
		Liar::Vector2* color = static_cast<Liar::Vector2*>(c);
		if (color) AddVertexBuffer(color->x, color->y);
	}

	void SubVector2VertexBuffer::SetVertexBuffer(Liar::Int index, Liar::Number x, Liar::Number y, Liar::Number, Liar::Number)
	{
		SetVertexBuffer(index, (void*)(new Liar::Vector2(x, y)));
	}

	void SubVector2VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index]) delete m_buffers[index];
		m_buffers[index] = static_cast<Liar::Vector2*>(color);
	}

	void SubVector2VertexBuffer::SetVertexBufferLen(Liar::Int len)
	{
		if (len == m_numberBuffers) return;
		Liar::Int i = 0;
		if (len < m_numberBuffers)
		{
			for (i = len; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
		}
		else
		{
			size_t blockSize = sizeof(Liar::Vector2*)*len;
			if (m_buffers) m_buffers = (Liar::Vector2**)realloc(m_buffers, blockSize);
			else m_buffers = (Liar::Vector2**)malloc(blockSize);

			for (i = m_numberBuffers; i < len; ++i) m_buffers[i] = nullptr;
		}
		m_numberBuffers = len;
	}

	void* SubVector2VertexBuffer::GetVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberBuffers) return nullptr;
		return m_buffers[index];
	}

	/**
	* vector3
	*/
	SubVector3VertexBuffer::SubVector3VertexBuffer() :
		Liar::ISubVertexBuffers(),
		m_buffers(nullptr), m_numberBuffers(0)
	{}

	SubVector3VertexBuffer::~SubVector3VertexBuffer()
	{
		if (m_buffers)
		{
			for (Liar::Int i = 0; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
			free(m_buffers);
			m_buffers = nullptr;
		}
	}

	Liar::Int SubVector3VertexBuffer::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
	}

	Liar::Int SubVector3VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
	}

	void SubVector3VertexBuffer::AddVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, (void**)m_buffers, m_numberBuffers, x, y, z, w);
		Liar::Vector3* color = static_cast<Liar::Vector3*>(buffer);
		if (!color)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			color = new Liar::Vector3(x, y, z);
			m_buffers[m_numberBuffers - 1] = color;
		}
	}

	void SubVector3VertexBuffer::AddVertexBuffer(void* c)
	{
		Liar::Vector3* color = static_cast<Liar::Vector3*>(c);
		if (color) AddVertexBuffer(color->x, color->y, color->z);
	}

	void SubVector3VertexBuffer::SetVertexBuffer(Liar::Int index, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number)
	{
		SetVertexBuffer(index, (void*)(new Liar::Vector3(x, y, z)));
	}

	void SubVector3VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index]) delete m_buffers[index];
		m_buffers[index] = static_cast<Liar::Vector3*>(color);
	}

	void SubVector3VertexBuffer::SetVertexBufferLen(Liar::Int len)
	{
		if (len == m_numberBuffers) return;
		Liar::Int i = 0;
		if (len < m_numberBuffers)
		{
			for (i = len; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
		}
		else
		{
			size_t blockSize = sizeof(Liar::Vector3*)*len;
			if (m_buffers) m_buffers = (Liar::Vector3**)realloc(m_buffers, blockSize);
			else m_buffers = (Liar::Vector3**)malloc(blockSize);

			for (i = m_numberBuffers; i < len; ++i) m_buffers[i] = nullptr;
		}
		m_numberBuffers = len;
	}

	void* SubVector3VertexBuffer::GetVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberBuffers) return nullptr;
		return m_buffers[index];
	}

	/**
	* vector4
	*/
	SubVector4VertexBuffer::SubVector4VertexBuffer() :
		Liar::ISubVertexBuffers(),
		m_buffers(nullptr), m_numberBuffers(0)
	{}

	SubVector4VertexBuffer::~SubVector4VertexBuffer()
	{
		if (m_buffers)
		{
			for (Liar::Int i = 0; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
			free(m_buffers);
			m_buffers = nullptr;
		}
	}

	Liar::Int SubVector4VertexBuffer::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR4;
	}

	Liar::Int SubVector4VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormat::ELEMENT_FORMAT_QUATERNION;
	}

	void SubVector4VertexBuffer::AddVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexElementSize::ELEMENT_SIZE_VECTOR4, (void**)m_buffers, m_numberBuffers, x, y, z, w);
		Liar::Quaternion* color = static_cast<Liar::Quaternion*>(buffer);
		if (!color)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			color = new Liar::Quaternion(x, y, z, w);
			m_buffers[m_numberBuffers - 1] = color;
		}
	}

	void SubVector4VertexBuffer::AddVertexBuffer(void* c)
	{
		Liar::Quaternion* color = static_cast<Liar::Quaternion*>(c);
		if (color) AddVertexBuffer(color->x, color->y, color->z, color->w);
	}

	void SubVector4VertexBuffer::SetVertexBuffer(Liar::Int index, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		SetVertexBuffer(index, (void*)(new Liar::Quaternion(x, y, z, w)));
	}

	void SubVector4VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index]) delete m_buffers[index];
		m_buffers[index] = static_cast<Liar::Quaternion*>(color);
	}

	void SubVector4VertexBuffer::SetVertexBufferLen(Liar::Int len)
	{
		if (len == m_numberBuffers) return;
		Liar::Int i = 0;
		if (len < m_numberBuffers)
		{
			for (i = len; i < m_numberBuffers; ++i)
			{
				if (m_buffers[i]) delete m_buffers[i];
			}
		}
		else
		{
			size_t blockSize = sizeof(Liar::Quaternion*)*len;
			if (m_buffers) m_buffers = (Liar::Quaternion**)realloc(m_buffers, blockSize);
			else m_buffers = (Liar::Quaternion**)malloc(blockSize);

			for (i = m_numberBuffers; i < len; ++i) m_buffers[i] = nullptr;
		}
		m_numberBuffers = len;
	}

	void* SubVector4VertexBuffer::GetVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberBuffers) return nullptr;
		return m_buffers[index];
	}
}