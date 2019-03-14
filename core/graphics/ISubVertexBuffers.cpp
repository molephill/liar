#include <core/graphics/ISubVertexBuffers.h>

namespace Liar
{
	void* ISubVertexBuffers::GetSubVertexBuffer(Liar::VertexElementSize type, void** buffers, size_t len, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		for (size_t i = 0; i < len; ++i)
		{
			void* buffer = buffers[i];
			switch (type)
			{
			case Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3:
			{
				Liar::Vector3* vec3 = static_cast<Liar::Vector3*>(buffer);
				if (vec3 && vec3->Equal(x, y, z)) return buffer;
				break;
			}
			case Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2:
			{
				Liar::Vector2* vec2 = static_cast<Liar::Vector2*>(buffer);
				if (vec2 && vec2->Equal(x, y)) return buffer;
				break;
			}
			case Liar::VertexElementSize::ELEMENT_SIZE_VECTOR4:
			{
				Liar::Quaternion* qua = static_cast<Liar::Quaternion*>(buffer);
				if (qua && qua->Equal(x, y, z, w)) return buffer;
				break;
			}
			}
		}

		return nullptr;
	}
}
