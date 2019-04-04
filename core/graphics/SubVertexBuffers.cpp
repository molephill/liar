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

	Liar::Int SubVector2VertexBuffer::GetSize() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
	}

	Liar::Int SubVector2VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormatSize::ELEMENT_FORMAT_VECTOR2;
	}

	void SubVector2VertexBuffer::AddVertexBuffer(void* c)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2, (void**)m_buffers, m_numberBuffers, c);
		if (!buffer)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			m_buffers[m_numberBuffers - 1] = static_cast<Liar::Vector2*>(c);
		}
	}

	void SubVector2VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index] != color && m_buffers[index]) delete m_buffers[index];
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

	void SubVector2VertexBuffer::ToString()
	{
		std::cout << "vector2 num:" << m_numberBuffers << std::endl;
		for (Liar::Int i = 0; i < m_numberBuffers; ++i)
		{
			std::cout << "index:" << i << " ";
			std::cout << *(m_buffers[i]) << std::endl;
		}
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

	Liar::Int SubVector3VertexBuffer::GetSize() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
	}

	Liar::Int SubVector3VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormatSize::ELEMENT_FORMAT_VECTOR3;
	}

	void SubVector3VertexBuffer::AddVertexBuffer(void* c)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3, (void**)m_buffers, m_numberBuffers, c);
		if (!buffer)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			m_buffers[m_numberBuffers - 1] = static_cast<Liar::Vector3*>(c);
		}
	}

	void SubVector3VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index] != color && m_buffers[index]) delete m_buffers[index];
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

	void SubVector3VertexBuffer::ToString()
	{
		std::cout << "vector3 num:" << m_numberBuffers << std::endl;
		for (Liar::Int i = 0; i < m_numberBuffers; ++i)
		{
			std::cout << "index:" << i << " ";
			std::cout << *(m_buffers[i]) << std::endl;
		}
	}

	/**
	* Vector4
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

	Liar::Int SubVector4VertexBuffer::GetSize() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR4;
	}

	Liar::Int SubVector4VertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormatSize::ELEMENT_FORMAT_VECTOR4;
	}


	void SubVector4VertexBuffer::AddVertexBuffer(void* c)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4, (void**)m_buffers, m_numberBuffers, c);
		if (!buffer)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			m_buffers[m_numberBuffers - 1] = static_cast<Liar::Vector4*>(c);
		}
	}

	void SubVector4VertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index] != color && m_buffers[index]) delete m_buffers[index];
		m_buffers[index] = static_cast<Liar::Vector4*>(color);
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
			size_t blockSize = sizeof(Liar::Vector4*)*len;
			if (m_buffers) m_buffers = (Liar::Vector4**)realloc(m_buffers, blockSize);
			else m_buffers = (Liar::Vector4**)malloc(blockSize);

			for (i = m_numberBuffers; i < len; ++i) m_buffers[i] = nullptr;
		}
		m_numberBuffers = len;
	}

	void* SubVector4VertexBuffer::GetVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberBuffers) return nullptr;
		return m_buffers[index];
	}

	void SubVector4VertexBuffer::ToString()
	{
		std::cout << "vector4 num:" << m_numberBuffers << std::endl;
		for (Liar::Int i = 0; i < m_numberBuffers; ++i)
		{
			std::cout << "index:" << i << " ";
			std::cout << *(m_buffers[i]) << std::endl;
		}
	}

	/**
	* Quat
	*/
	SubQuatVertexBuffer::SubQuatVertexBuffer() :
		Liar::ISubVertexBuffers(),
		m_buffers(nullptr), m_numberBuffers(0)
	{}

	SubQuatVertexBuffer::~SubQuatVertexBuffer()
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

	Liar::Int SubQuatVertexBuffer::GetSize() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_QUATERNION;
	}

	Liar::Int SubQuatVertexBuffer::GetFormat() const
	{
		return Liar::VertexElementFormatSize::ELEMENT_FORMAT_QUATERNION;
	}

	void SubQuatVertexBuffer::AddVertexBuffer(void* c)
	{
		void* buffer = GetSubVertexBuffer(Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION, (void**)m_buffers, m_numberBuffers, c);
		if (!buffer)
		{
			SetVertexBufferLen(m_numberBuffers + 1);
			m_buffers[m_numberBuffers - 1] = static_cast<Liar::Quaternion*>(c);
		}
	}

	void SubQuatVertexBuffer::SetVertexBuffer(Liar::Int index, void* color)
	{
		if (m_buffers[index] != color && m_buffers[index]) delete m_buffers[index];
		m_buffers[index] = static_cast<Liar::Quaternion*>(color);
	}

	void SubQuatVertexBuffer::SetVertexBufferLen(Liar::Int len)
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

	void* SubQuatVertexBuffer::GetVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberBuffers) return nullptr;
		return m_buffers[index];
	}

	void SubQuatVertexBuffer::ToString()
	{
		std::cout << "quat num:" << m_numberBuffers << std::endl;
		for (Liar::Int i = 0; i < m_numberBuffers; ++i)
		{
			std::cout << "index:" << i << " ";
			std::cout << *(m_buffers[i]) << std::endl;
		}
	}
}