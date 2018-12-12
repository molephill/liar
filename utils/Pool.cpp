
#include <utils/Pool.h>

#include <math/Matrix4x4.h>
#include <core/render/RenderUnit.h>

namespace Liar
{
	Pool::Pool():
		m_createPointers(nullptr), m_numberCreatePoint(nullptr), m_numberCreate(0),
		m_recoveryPoints(nullptr), m_numberRecorverPoint(nullptr), m_numberRecover(0)
	{

	}


	Pool::~Pool()
	{
	}

	size_t Pool::GetPointerTrip(Liar::PoolType type)
	{
		switch (type)
		{
		case Liar::PoolType::POOL_TYPE_VECTOR3:
			return sizeof(Liar::Vector3*);
		case Liar::PoolType::POOL_TYPE_VECTOR4:
		case Liar::PoolType::POOL_TYPE_QUATERNION:
			return sizeof(Liar::Vector4*);
		case Liar::PoolType::POOL_TYPE_MATRIX4x4:
			return sizeof(Liar::Matrix4x4*);
		case Liar::PoolType::POOL_TYPE_RENDERUNIT :
			return sizeof(Liar::RenderUnit);
		default:
			return 0;
		}
	}

	void Pool::Create(Liar::PoolType type)
	{
		if (type >= m_numberCreate)
		{
			m_numberCreate = type + 1;
			size_t trip = GetPointerTrip(type);
			if (m_createPointers)
			{
				m_createPointers = (void**)realloc(m_createPointers, trip*m_numberCreate);
				m_numberCreatePoint = (int*)realloc(m_numberCreatePoint, sizeof(int*)*m_numberCreate);
			}
			else
			{
				m_createPointers = (void**)malloc(trip*m_numberCreate);
				m_numberCreatePoint = (int*)malloc(sizeof(int*)*m_numberCreate);
			}
		}
	}

	void* Pool::PopPointer(Liar::PoolType type)
	{
		if (type >= m_numberRecover)
		{

		}
	}

	void Pool::PushPointer(Liar::PoolType type, void* pointer)
	{
		if (pointer)
		{
			if (type >= m_numberRecover)
			{
				m_numberRecover = type + 1;
				size_t trip = GetPointerTrip(type);
				if (m_numberRecorverPoint)
				{
					m_recoveryPoints = (void**)realloc(m_recoveryPoints, trip*m_numberRecover);
					m_numberRecorverPoint = (int*)realloc(m_numberRecorverPoint, sizeof(int*)*m_numberRecover);
				}
				else
				{
					m_recoveryPoints = (void**)malloc(trip*m_numberRecover);
					m_numberRecorverPoint = (int*)malloc(sizeof(int*)*m_numberRecover);
				}
			}
			m_recoveryPoints[m_numberRecorverPoint[type]++] = pointer;
		}
	}
}