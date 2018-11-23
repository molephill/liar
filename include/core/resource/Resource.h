#pragma once

#include <LiarType.h>

namespace Liar
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

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
		Liar::Int AddRefrence();
		Liar::Int RemoveRefrence();
		virtual bool Destroy();
		virtual bool ReleaseResource(bool force = false);
		virtual void ActiveResource(bool force = false);

	protected:
		virtual void DisposeResource() = 0;
		virtual void RecreateResource() = 0;

	public:
		Liar::Int GetRefrenceCount() const { return m_refrenceCount; };
		Liar::Uint GetID() const { return m_id; };
	};
}

