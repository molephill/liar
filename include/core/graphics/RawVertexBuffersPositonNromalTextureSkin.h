#pragma once

#include "RawVertexBuffersPositionNormalTexture.h"

namespace Liar
{
	class RawVertexBuffersPositonNromalTextureSkin:public Liar::RawVertexBuffersPositionNormalTexture
	{
	public:
		RawVertexBuffersPositonNromalTextureSkin(Liar::GeometryVertexType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonNromalTextureSkin();

	protected:
		Liar::SubVector2VertexBuffer* m_texCoord;
	};
}