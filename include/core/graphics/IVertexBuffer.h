#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <string>

namespace Liar
{
	static const char* VERTEX_ATTRIB_POSITION0 = "POSITION0";
	static const char* VERTEX_ATTRIB_NORMAL0 = "NORMAL0";
	static const char* VERTEX_ATTRIB_TEXCOORDINATE0 = "TEXCOORDNIATE0";

	class IVertexBuffer
	{
	public:
		IVertexBuffer() {};
		virtual ~IVertexBuffer() {};

	public:
		virtual void SetAttrData(Liar::VertexElementAttr, void*) = 0;
		virtual void BufferSubData(GLenum type, size_t) = 0;
		virtual size_t GetStride() const = 0;
		virtual void VertexAttrbPointer() = 0;
		virtual std::string GetAttribDefines() = 0;
	};
}