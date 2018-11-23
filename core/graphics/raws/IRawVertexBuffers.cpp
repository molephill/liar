#pragma once

#include <core/graphics/raws/IRawVertexBuffers.h>

namespace Liar
{
	IRawVertexBuffers::IRawVertexBuffers()
	{
	}

	IRawVertexBuffers::~IRawVertexBuffers()
	{
		Destroy();
	}

	void* IRawVertexBuffers::GetVertexBuffer(Liar::VertexElementAttr attr, void** buffers, size_t len, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		void* out = nullptr;
		for (size_t i = 0; i < len; ++i)
		{
			void* buffer = buffers[i];
			switch (attr)
			{
			case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			{
				Liar::Vector3* vec3 = static_cast<Liar::Vector3*>(buffer);
				if (vec3 && vec3->Equal(x, y, z)) return buffer;
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			{
				Liar::Vector2* vec2 = static_cast<Liar::Vector2*>(buffer);
				if (vec2 && vec2->Equal(x, y)) return buffer;
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			{
				Liar::Quaternion* qua = static_cast<Liar::Quaternion*>(buffer);
				if (qua && qua->Equal(x, y, z, w)) return buffer;
				break;
			}
			}
		}

		return out;
	}
}