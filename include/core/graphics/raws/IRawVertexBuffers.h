#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	class IRawVertexBuffers
	{
	public:
		IRawVertexBuffers() {};
		virtual ~IRawVertexBuffers() 
		{
			Destroy();
		};

	protected:

		void* GetVertexBuffer(Liar::VertexElementAttr attr, void** buffers, size_t len, Liar::Number x, Liar::Number y, Liar::Number z = 0.0f, Liar::Number w = 0.0f)
		{
			void* out = nullptr;
			for (size_t i = 0; i < len; ++i)
			{
				void* buffer = buffers[i];
				switch (attr)
				{
				case Liar::VertexElementAttr::POSITION:
				case Liar::VertexElementAttr::NORMAL:
					Liar::Vector3* vec3 = static_cast<Liar::Vector3*>(buffer);
					if (vec3 && vec3->Equal(x, y, z)) return buffer;
					break;
				case Liar::VertexElementAttr::TEXTURECOORDINATE:
					Liar::Vector2* vec2 = static_cast<Liar::Vector2*>(buffer);
					if (vec2 && vec2->Equal(x, y)) return buffer;
					break;
				case Liar::VertexElementAttr::ROTATION:
					Liar::Quaternion* qua = static_cast<Liar::Quaternion*>(buffer);
					if (qua && qua->Equal(x, y, z, w)) return buffer;
					break;
				}
			}

			return out;
		};

		virtual void Destroy() = 0;

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f) = 0;
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t) = 0;
	};
}