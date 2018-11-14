#pragma once

#include <events/EventDispatcher.h>
#include <core/render/IUpdate.h>
#include <LiarType.h>

namespace Liar
{
	class ComponenetNode;

	class Component3D:public EventDispatcher, public IUpdate
	{
	public:
		Component3D():
			Liar::EventDispatcher(),
			Liar::IUpdate(),
			m_destroyed(false),m_id(0),m_owner(nullptr),
			m_enable(false),started(false)
		{};
		~Component3D() {};

	protected:
		bool m_destroyed;
		Liar::Uint m_id;
		bool m_enable;
		Liar::ComponenetNode* m_owner;

	public:
		bool started;

	public:
		Liar::Uint GetId() const { return m_id; };
		Liar::ComponenetNode* GetOwner() const { return m_owner; };
		bool GetEnable() const { return m_enable; };
		bool GetDestroyed() const { return m_destroyed; };
		void SetEnable(bool value) { m_enable = value; };

	public:
		inline virtual void Initialize(Liar::ComponenetNode* owner)
		{
			m_owner = owner;
			m_enable = true;
			started = false;
			Load(owner);
		};

		inline virtual void Destroy()
		{
			Unload(m_owner);
			m_owner = nullptr;
			m_destroyed = true;
		};

		virtual void Load(Liar::ComponenetNode*) {};
		virtual void Unload(Liar::ComponenetNode*) {};
		virtual void Start(Liar::RenderState*) {};
		virtual void Update(Liar::RenderState*) {};
		virtual void LateUpdate(Liar::RenderState*) {};
		virtual void PreRenderUpdate(Liar::RenderState*) {};
		virtual void PostRenderUpdate(Liar::RenderState*) {};
	};
}