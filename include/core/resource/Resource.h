#pragma once

#include <LiarType.h>
#include <string>

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
		std::string m_url;

	public:
		virtual Liar::Int AddRefrence();
		virtual Liar::Int ReduceRefrence();
		virtual bool ReleaseResource(bool = false);
		virtual void ActiveResource(bool = false);

	protected:
		virtual void DisposeResource() = 0;
		virtual void RecreateResource();
		void Dispose();

	public:
		Liar::Uint GetID() const { return m_id; };
		bool GetLoaded() const { return m_loaded; };
		Liar::Boolen Equals(const char* path) const { return m_url == path; };
		Liar::Boolen Equals(const Liar::Resource& rhs) const { return rhs.m_url == m_url; };
		Liar::Boolen operator==(const char* path) const { return m_url == path; };
		Liar::Boolen operator==(const Liar::Resource& rhs) const { return rhs.m_url == m_url; };
		virtual void SetURL(const char*) = 0;
	};
}

