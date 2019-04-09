#pragma once

#include <string>

namespace Liar
{
	class ByteArray
	{
	public:
		ByteArray();
		~ByteArray();

	public:
		static ByteArray* Create(int, int = ENDIAN_LITTLE);

		//C++中创建使用,不导出至LUA
		static ByteArray* CreateWithBuffer(char*, int, int = ENDIAN_LITTLE);

		static int CheckCPUEndian();

		static const int ENDIAN_LITTLE = 0;
		static const int ENDIAN_BIG = 1;

		bool ReadBool();
		void WriteBool(bool);

		short ReadShort();
		void WriteShort(short);

		unsigned short ReadUnsignedShort();
		void WriteUnsignedShort(unsigned short);

		int ReadInt();
		void WriteInt(int);

		float ReadFloat();
		void WriteFloat(float);

		/**
		* 从字节流中读取一个无符号的 32 位整数。
		* 32位系统下int与long同4字节
		**/
		unsigned int RadUnsignedInt();
		void WriteUnsignedInt(unsigned int);

		long long ReadLongLong();
		void WriteLongLong(long long);

		std::string ReadString(int);
		void WriteString(std::string);

		char ReadByte();
		void WriteByte(char);

		unsigned char ReadUnsignedByte();
		void WriteUnsignedChar(unsigned char);

		const char* GetBuffer();
		void Clear();

		int GetEndian();
		void SetEndian(int);

		int GetPosition();
		void SetPosition(int);

		int GetBytesAvailable();
		int GetLength();

	private:
		void copyMemory(void*, const void*, int);

		char* m_buffer;
		int m_pos;
		int m_length;
		int m_endian;
		short m_flag;
	};
}

