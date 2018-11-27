#pragma once

#include <core/display/EventDispatcher.h>
#include <LiarType.h>

namespace Liar
{
	class Node:public EventDispatcher
	{
	public:
		Node();
		~Node();

	protected:
		int m_bits;
		Liar::Node** m_childs;
		Liar::Uint m_numberChild;
		Liar::Node* m_parent;
		const char* m_name;
		bool m_destroyed;
		bool m_visible;

	public:
		virtual void SetUpNoticeType(int);
		virtual bool Destroy(bool destroyChild = true);
		virtual void DestroyChildren();
		virtual Liar::Node* AddChild(Liar::Node*);
		virtual Liar::Node* AddChildAt(Liar::Node*, Liar::Int);
		Liar::Int GetChildIndex(Liar::Node*) const;
		virtual Liar::Node* RemoveChild(Liar::Node*);
		virtual Liar::Node* RemoveChildAt(Liar::Int);
		Liar::Node* GetChildAt(Liar::Int);
		virtual void RemoveChildren(Liar::Int beginIndex = 0, Liar::Int endIndex = 0x7fffffff);
		virtual void RemoveSelf();
		virtual Liar::Node* GetChildByName(const char*);
		virtual Liar::Node* RemoveChildByName(const char*);
		virtual Liar::Node* ReplaceChild(Liar::Node*, Liar::Node*);

		virtual void SpliceChild(Liar::Uint, Liar::Uint, bool destroy = false);
		virtual Liar::Node* SpliceChild(Liar::Uint, Liar::Node*);
		virtual void SpliceChild(Liar::Uint, bool destroy = false);
		virtual bool Contains(Liar::Node*) const;
		virtual void SetParent(Liar::Node*);
		virtual void SetVisible(bool);

	protected:
		virtual void ChildChange(Liar::Node* child = nullptr) {};

	public:
		inline bool GetDestroyed() const { return m_destroyed; };
		inline bool GetBit(int type) const { return (m_bits & type) != 0; };
		inline void SetBit(int type, bool value) { if (value) m_bits |= type; else m_bits &= ~type; };
		Liar::Node* GetParent() const { return m_parent; };
		virtual Liar::Uint NumChildren() const { return m_numberChild; };
		bool GetVisible() const { return m_visible; };

	private:
		void DisplayChild(Liar::Node*, bool);
	};
}

