#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	class ISubVertexBuffers
	{
	public:
		ISubVertexBuffers() {};
		virtual ~ISubVertexBuffers() {};

	protected:
		void* GetSubVertexBuffer(Liar::VertexFormatType, void**, size_t, void*);

	public:
		virtual Liar::Int GetStride() const = 0;
		virtual Liar::Int GetFormat() const = 0;

		virtual void AddVertexBuffer(void*) = 0;
		virtual void SetVertexBuffer(Liar::Int, void*) = 0;
		virtual void SetVertexBufferLen(Liar::Int) = 0;
		virtual void* GetVertexBuffer(Liar::Int) const = 0;
	};
}
