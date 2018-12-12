#pragma once

namespace Liar
{
	enum PoolType
	{
		POOL_TYPE_VECTOR3,
		POOL_TYPE_VECTOR4,
		POOL_TYPE_QUATERNION,
		POOL_TYPE_MATRIX4x4,
		POOL_TYPE_RENDERUNIT
	};

	class Pool
	{
	public:
		Pool();
		~Pool();

	private:
		void** m_createPointers;
		int* m_numberCreatePoint;
		int m_numberCreate;

		void** m_recoveryPoints;
		int* m_numberRecorverPoint;
		int m_numberRecover;

	private:
		size_t GetPointerTrip(Liar::PoolType);

	public:
		void* PopPointer(Liar::PoolType);
		void PushPointer(Liar::PoolType, void*);

	private:
		void Create(Liar::PoolType);
	};
}