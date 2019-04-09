
#include <math/ByteArray.h>

namespace Liar
{
	ByteArray::ByteArray() :
		m_buffer(nullptr),
		m_pos(0),
		m_length(0),
		m_endian(ENDIAN_LITTLE),
		m_flag(-1)
	{

	};

	ByteArray::~ByteArray()
	{
		if (this->m_flag == 0 && this->m_buffer) 
		{
			delete[] this->m_buffer;
			this->m_buffer = nullptr;
			this->m_flag = -1;
		}
	};

	ByteArray* ByteArray::Create(int len, int endian)
	{
		ByteArray* ba = new ByteArray();
		if (ba)
		{
			ba->m_buffer = new char[len];
			ba->m_endian = endian;
			ba->m_length = len;
			ba->m_flag = 0;
		}
		else 
		{
			delete ba;
			ba = nullptr;
			return nullptr;
		}

		return ba;
	}

	ByteArray* ByteArray::CreateWithBuffer(char* buffer, int len, int endian)
	{
		ByteArray* ba = new ByteArray();
		if (ba)
		{
			ba->m_buffer = buffer;
			ba->m_length = len;
			ba->m_flag = 0;
			return ba;
		}
		else 
		{
			delete ba;
			ba = nullptr;
			return nullptr;
		}
		return ba;
	}

	bool ByteArray::ReadBool()
	{
		bool b;
		char* p = (char*)&b;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(b));
		this->m_pos += sizeof(b);
		return b;
	}

	void ByteArray::WriteBool(bool value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += sizeof(value);
	}


	short ByteArray::ReadShort()
	{
		short n = 0;
		char* p = (char*)&n;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(n));
		this->m_pos += 2;
		return n;
	}

	void ByteArray::WriteShort(short value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 2;
	}

	int ByteArray::ReadInt() 
	{
		int n;
		char* p = (char*)&n;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(n));
		this->m_pos += 4;
		return n;
	}


	void ByteArray::WriteInt(int value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 4;
	}

	float ByteArray::ReadFloat()
	{
		float n = 0.0f;
		char* p = (char*)&n;
		size_t len = sizeof(n);
		copyMemory(p, this->m_buffer + this->m_pos, len);
		this->m_pos += len;
		return n;
	}

	void ByteArray::WriteFloat(float value)
	{
		char* p = (char*)&value;
		size_t len = sizeof(value);
		memcpy(this->m_buffer + this->m_pos, p, len);
		this->m_pos += len;
	}

	unsigned int ByteArray::RadUnsignedInt() 
	{
		unsigned int n;
		char* p = (char*)&n;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(n));

		this->m_pos += 4;
		return n;
	}


	void ByteArray::WriteUnsignedInt(unsigned int value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 4;
	}


	unsigned short ByteArray::ReadUnsignedShort() 
	{
		unsigned short n;
		char* p = (char*)&n;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(n));
		this->m_pos += 2;
		return n;
	}


	void ByteArray::WriteUnsignedShort(unsigned short value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 2;
	}


	char ByteArray::ReadByte() 
	{
		signed char val = this->m_buffer[this->m_pos];
		if (val > 127) {
			val = val - 255;
		}
		this->m_pos += 1;
		return val;
	}


	void ByteArray::WriteByte(char value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 1;
	}


	unsigned char ByteArray::ReadUnsignedByte() 
	{
		unsigned char val = this->m_buffer[this->m_pos];
		this->m_pos += 1;
		return val;
	}


	void ByteArray::WriteUnsignedChar(unsigned char value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += 1;
	}


	long long ByteArray::ReadLongLong()
	{
		long long n;
		char* p = (char*)&n;
		copyMemory(p, this->m_buffer + this->m_pos, sizeof(n));
		this->m_pos += sizeof(n);
		return n;
	}


	void ByteArray::WriteLongLong(long long value)
	{
		char* p = (char*)&value;
		memcpy(this->m_buffer + this->m_pos, p, sizeof(value));
		this->m_pos += sizeof(value);
	}


	std::string ByteArray::ReadString(int len)
	{
		char* value = new char[len + 1];

		value[len] = '\0';
		copyMemory(value, this->m_buffer + this->m_pos, len);
		this->m_pos += len;

		std::string str(value);
		delete[] value;
		value = nullptr;

		return str;
	}

	void ByteArray::WriteString(std::string value)
	{
		auto len = value.length();
		const char* p = value.c_str();
		memcpy(this->m_buffer + this->m_pos, p, len);
		this->m_pos += len;
	}

	void ByteArray::copyMemory(void* to, const void* from, int len)
	{
		char* t = (char*)to;
		char* f = (char*)from;
		if (m_endian == ENDIAN_LITTLE)
		{
			memcpy(t, f, len);
		}
		else if (m_endian == ENDIAN_BIG)
		{
			for (int i = len - 1; i >= 0; i--)
			{
				t[(len - 1) - i] = f[i];
			}
		}
	}


	const char* ByteArray::GetBuffer()
	{
		return this->m_buffer;
	}

	void ByteArray::Clear()
	{
		memset(this->m_buffer, 0, this->m_length);
	}

	//0: little 1:big
	int ByteArray::CheckCPUEndian() 
	{
		union w
		{
			int a;
			char b;
		} c;
		c.a = 1;
		return  (c.b == 1 ? ENDIAN_LITTLE : ENDIAN_BIG);
	}


	void ByteArray::SetEndian(int n)
	{
		this->m_endian = n;
	}


	int ByteArray::GetEndian()
	{
		return this->m_endian;
	}


	int ByteArray::GetPosition()
	{
		return this->m_pos;
	}

	void ByteArray::SetPosition(int pos)
	{
		this->m_pos = pos;
	}

	int ByteArray::GetLength()
	{
		return this->m_length;
	}

	int ByteArray::GetBytesAvailable()
	{
		return this->m_length - this->m_pos;
	}
}