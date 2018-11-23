#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>

namespace Liar
{
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
	};
}