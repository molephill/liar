#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	class ISubVertexKey
	{
	public:
		ISubVertexKey() {};
		virtual ~ISubVertexKey() {};

	public:
		virtual void SetIndex(Liar::Uint) = 0;
		virtual Liar::Uint GetIndex() const = 0;
		virtual Liar::ISubVertexKey* Clone() const = 0;

		inline Liar::Boolen operator==(const Liar::ISubVertexKey& key) const
		{
			return this->GetIndex() == key.GetIndex();
		};

		inline friend std::ostream& operator<<(std::ostream& os, const Liar::ISubVertexKey& key)
		{
			os << key.GetIndex();
			return os;
		};
	};

	class ISubVertexBuffers
	{
	public:
		ISubVertexBuffers() {};
		virtual ~ISubVertexBuffers() {};

	protected:
		void* GetSubVertexBuffer(Liar::VertexElementSize, void**, size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);

	public:
		virtual Liar::Int GetStride() const = 0;
		virtual Liar::Int GetFormat() const = 0;

		virtual void AddVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) = 0;
		virtual void AddVertexBuffer(void*) = 0;

		virtual void SetVertexBuffer(Liar::Int, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) = 0;
		virtual void SetVertexBuffer(Liar::Int, void*) = 0;

		virtual void SetVertexBufferLen(Liar::Int) = 0;
		virtual void* GetVertexBuffer(Liar::Int) const = 0;
	};
}
