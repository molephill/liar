#pragma once

#include <core/graphics/IVertexBuffer.h>
#include <math/Vector3.h>
#include <math/Vector2.h>

namespace Liar
{
	class VertexBufferPositionNormalTexture:public IVertexBuffer
	{
	public:
		VertexBufferPositionNormalTexture() :
			Liar::IVertexBuffer()
		{};
		~VertexBufferPositionNormalTexture() 
		{
			m_position = nullptr;
			m_normal = nullptr;
			m_texCoord = nullptr;
		};

	private:
		Liar::Vector3* m_position;
		Liar::Vector3* m_normal;
		Liar::Vector2* m_texCoord;

	public:
		virtual void SetAttrData(Liar::VertexElementAttr type, void* value)
		{
			switch (type)
			{
			case Liar::VertexElementAttr::POSITION:
				m_position = static_cast<Liar::Vector3*>(value);
				break;
			case Liar::VertexElementAttr::NORMAL:
				m_normal = static_cast<Liar::Vector3*>(value);
				break;
			case Liar::VertexElementAttr::TEXTURECOORDINATE:
				m_texCoord = static_cast<Liar::Vector2*>(value);
				break;
			}
		};

		virtual void BufferSubData(GLenum type, size_t start)
		{
			size_t positionOffsize = start;
			size_t normalOffsize = start + Liar::VertexElementSize::VECTOR3;
			size_t colorOffseize = normalOffsize + Liar::VertexElementFormat::VECTOR3;
			Liar::GL::mainContext.BufferSubData(type, positionOffsize, Liar::VertexElementSize::VECTOR3, m_position);
			Liar::GL::mainContext.BufferSubData(type, normalOffsize, Liar::VertexElementSize::VECTOR3, m_normal);
			Liar::GL::mainContext.BufferSubData(type, colorOffseize, Liar::VertexElementSize::VECTOR2, m_texCoord);
		}

		virtual size_t GetStride() const
		{
			return  Liar::VertexElementSize::VECTOR3 + Liar::VertexElementSize::VECTOR3 + Liar::VertexElementSize::VECTOR2;
		}

		virtual void VertexAttrbPointer()
		{
			Liar::GLContext& gl = Liar::GL::mainContext;
			size_t stride = GetStride();
			// position
			gl.VertexAttribPointer(Liar::VertexElementAttr::POSITION, Liar::VertexElementFormat::VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)0);
			gl.EnableVertexAttribArray(0);
			// normal
			gl.VertexAttribPointer(Liar::VertexElementAttr::NORMAL, Liar::VertexElementFormat::VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)Liar::VertexElementSize::VECTOR3);
			gl.EnableVertexAttribArray(1);
			// texCoordinate
			gl.VertexAttribPointer(Liar::VertexElementAttr::TEXTURECOORDINATE, Liar::VertexElementFormat::VECTOR2, GL_FLOAT, GL_FALSE, stride, (void*)Liar::VertexElementSize::VECTOR3_DOUBLE);
			gl.EnableVertexAttribArray(2);
		}
	};
}