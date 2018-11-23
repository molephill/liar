
#include <core/resource/Resource.h>

namespace Liar
{
	Resource::Resource():
		m_id(++__uniqueIDCounter),
		m_memorySize(0),
		m_released(true), m_destroyed(false),
		m_lock(false), m_loaded(true), m_refrenceCount(0)
	{}

	Resource::~Resource()
	{
		Destroy();
	}

	Liar::Int Resource::AddRefrence()
	{
		return m_refrenceCount++;
	}

	Liar::Int Resource::RemoveRefrence()
	{
		return m_refrenceCount--;
	}

	bool Resource::Destroy()
	{
		if (m_destroyed) return false;
		m_lock = false;
		ReleaseResource();
		m_destroyed = true;
		return true;

	}

	bool Resource::ReleaseResource(bool force)
	{
		if (!force && m_lock) return false;
		if (!m_released || force)
		{
			DisposeResource();
			m_released = true;
		}
		return true;
	}

	void Resource::ActiveResource(bool force)
	{
		if (!m_destroyed && m_loaded && (m_released || force))
		{
			RecreateResource();
		}
	}

	Liar::Uint Resource::__uniqueIDCounter = 0;
}