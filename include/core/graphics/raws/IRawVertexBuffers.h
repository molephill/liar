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
		IRawVertexBuffers();
		virtual ~IRawVertexBuffers();

	protected:
		void* GetVertexBuffer(Liar::VertexElementAttr, void**, size_t, Liar::Number, Liar::Number, Liar::Number z = 0.0f, Liar::Number w = 0.0f);
		virtual void Destroy() {};

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f) = 0;
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t) = 0;
	};
}