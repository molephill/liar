#pragma once

#include <LiarType.h>

namespace Liar
{
	class Resource
	{
	public:
		Resource():
			m_id(++__uniqueIDCounter),
			m_memorySize(0),
			m_released(true), m_destroyed(false), m_lock(false), m_loaded(true),
			m_refrenceCount(0)
		{
		};
		~Resource()
		{
			Destroy();
		};

	private:
		static Liar::Uint __uniqueIDCounter;

	protected:
		Liar::Uint m_id;
		Liar::Uint m_memorySize;
		bool m_released;
		bool m_destroyed;
		bool m_lock;
		bool m_loaded;
		Liar::Int m_refrenceCount;

	public:
		inline Liar::Int AddRefrence()
		{
			return m_refrenceCount++;
		};

		inline Liar::Int RemoveRefrence()
		{
			return m_refrenceCount--;
		}

		virtual bool Destroy()
		{
			if (m_destroyed) return false;
			m_lock = false;
			ReleaseResource();
			m_destroyed = true;
		}

		virtual bool ReleaseResource(bool force = false)
		{
			if (!force && m_lock) return false;
			if (!m_released || force)
			{
				DisposeResource();
				m_released = true;
			}
		}

		virtual void ActiveResource(bool force = false)
		{
			if (!m_destroyed && m_loaded && (m_released || force))
			{
				RecreateResource();
			}
		}

	protected:
		virtual void DisposeResource() = 0;
		virtual void RecreateResource() = 0;

	public:
		Liar::Int GetRefrenceCount() const { return m_refrenceCount; };
		Liar::Uint GetID() const { return m_id; };
	};

	Liar::Uint Resource::__uniqueIDCounter = 0;
}

