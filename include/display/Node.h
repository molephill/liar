#pragma once

#include <events/EventDispatcher.h>
#include <LiarType.h>

namespace Liar
{
	class Node:public EventDispatcher
	{
	public:
		Node();
		~Node();

	private:
		int m_bits;
		Liar::Node** m_childs;
		Liar::Uint m_numberChild;
		Liar::Node* m_parent;
		const char* m_name;
		bool m_destroyed;
		bool m_visible;

	public:
		void SetUpNoticeType(int);
		void Destroy(bool destroyChild = true);
		void DestroyChildren();
		Liar::Node* AddChild(Liar::Node*);
		Liar::Node* AddChildAt(Liar::Node*, Liar::Int);
		Liar::Int GetChildIndex(Liar::Node*) const;
		Liar::Node* RemoveChild(Liar::Node*);
		Liar::Node* RemoveChildAt(Liar::Int);
		Liar::Node* GetChildAt(Liar::Int);
		void RemoveChildren(Liar::Int beginIndex = 0, Liar::Int endIndex = 0x7fffffff);
		void RemoveSelf();
		Liar::Node* GetChildByName(const char*);
		Liar::Node* RemoveChildByName(const char*);
		Liar::Node* ReplaceChild(Liar::Node*, Liar::Node*);

		void SpliceChild(Liar::Uint, Liar::Uint, bool destroy = false);
		Liar::Node* SpliceChild(Liar::Uint, Liar::Node*);
		void SpliceChild(Liar::Uint, bool destroy = false);
		bool Contains(Liar::Node*) const;
		void SetParent(Liar::Node*);
		void SetVisible(bool);

	protected:
		virtual void ChildChange(Liar::Node* child = nullptr) {};

	public:
		inline bool GetDestroyed() const { return m_destroyed; };
		inline bool GetBit(int type) const { return (m_bits & type) != 0; };
		inline void SetBit(int type, bool value) { if (value) m_bits |= type; else m_bits &= ~type; };
		Liar::Node* GetParent() const { return m_parent; };
		Liar::Uint NumChildren() const { return m_numberChild; };
		bool GetVisible() const { return m_visible; };

	private:
		void DisplayChild(Liar::Node*, bool);
	};
}

