#pragma once

#include <core/graphics/IVertexBuffer.h>
#include <math/Vector2.h>
#include <math/Vector3.h>

namespace Liar
{
	class VertexBufferPositionNormalTexture:public IVertexBuffer
	{
	public:
		VertexBufferPositionNormalTexture();
		~VertexBufferPositionNormalTexture();

	private:
		Liar::Vector3* m_position;
		Liar::Vector3* m_normal;
		Liar::Vector2* m_texCoord;

	public:
		virtual void SetAttrData(Liar::VertexElementAttr type, void* value);
		virtual void BufferSubData(GLenum type, size_t start);
		virtual size_t GetStride() const;
		virtual void VertexAttrbPointer();
	};
}