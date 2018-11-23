
#include <core/graphics/VertexBufferPositionNormalTexture.h>
#include <core/graphics/VertexElementUsage.h>
#include <Liar3D.h>

namespace Liar
{
	VertexBufferPositionNormalTexture::VertexBufferPositionNormalTexture() :
		Liar::IVertexBuffer(),
		m_position(nullptr), m_normal(nullptr), m_texCoord(nullptr)
	{}

	VertexBufferPositionNormalTexture::~VertexBufferPositionNormalTexture()
	{
		m_position = nullptr;
		m_normal = nullptr;
		m_texCoord = nullptr;
	}


	void VertexBufferPositionNormalTexture::SetAttrData(Liar::VertexElementAttr type, void* value)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_position = static_cast<Liar::Vector3*>(value);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			m_normal = static_cast<Liar::Vector3*>(value);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			m_texCoord = static_cast<Liar::Vector2*>(value);
			break;
		}
	}

	void VertexBufferPositionNormalTexture::BufferSubData(GLenum type, size_t start)
	{
		size_t positionOffsize = start;
		size_t normalOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
		size_t texCoordOffseize = normalOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		gl.BufferSubData(type, positionOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, m_position);
		gl.BufferSubData(type, normalOffsize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, m_normal);
		gl.BufferSubData(type, texCoordOffseize, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2, m_texCoord);
	}

	size_t VertexBufferPositionNormalTexture::GetStride() const
	{
		return  Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
	}

	void VertexBufferPositionNormalTexture::VertexAttrbPointer()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		size_t stride = GetStride();
		size_t positionOffsize = 0;
		size_t normalOffsize = positionOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3;
		size_t texCoordOffseize = normalOffsize + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
		// position
		gl.VertexAttribPointer(Liar::VertexElementUsage::POSITION0, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)positionOffsize);
		gl.EnableVertexAttribArray(Liar::VertexElementUsage::POSITION0);
		// normal
		gl.VertexAttribPointer(Liar::VertexElementUsage::NORMAL0, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(Liar::VertexElementUsage::NORMAL0);
		// texCoordinate
		gl.VertexAttribPointer(Liar::VertexElementUsage::TEXTURECOORDINATE0, Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffseize);
		gl.EnableVertexAttribArray(Liar::VertexElementUsage::TEXTURECOORDINATE0);
	}
}