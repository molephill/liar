#include <core/display/Node.h>

namespace Liar
{
	Node::Node():
		Liar::EventDispatcher(),
		m_bits(0), m_numberChild(0), m_childs(nullptr),
		m_parent(nullptr), m_name(nullptr), m_destroyed(false),
		m_visible(true)
	{
	}

	Node::~Node()
	{
		Destroy();
	}

	void Node::SetUpNoticeType(int type)
	{
		Liar::Node* ele = this;
		ele->SetBit(type, true);
		ele = ele->m_parent;
		while (ele)
		{
			if (ele->GetBit(type)) return;
			ele->SetBit(type, true);
			ele = ele->m_parent;
		}
	}

	void Node::SpliceChild(Liar::Uint startIndex, Liar::Uint len, bool destroy)
	{
		Liar::Uint calcLen = 0;
		Liar::Uint replaceIndex = startIndex + len;
		Liar::Uint max = std::max(replaceIndex, m_numberChild);
		for (Liar::Uint i = startIndex; i < max; ++i)
		{
			if (calcLen > len) break;
			Liar::Node* node = m_childs[i];
			if (destroy) node->~Node();
			m_childs[i] = m_childs[replaceIndex++];
		}

		if (destroy)
		{
			replaceIndex = startIndex + len;
			for (Liar::Uint i = replaceIndex; i < max; ++i)
			{
				free(m_childs[i]);
				m_childs[i] = nullptr;
			}
		}

		m_numberChild -= (max - startIndex);
	}

	Liar::Node* Node::SpliceChild(Liar::Uint startIndex, Liar::Node* node)
	{
		if (!node || m_destroyed) return node;
		if (!m_childs)
		{
			m_childs = (Liar::Node**)malloc(sizeof(Liar::Node*));
			m_childs[0] = node;
		}
		else
		{
			startIndex = std::min(m_numberChild - 1, startIndex);
			m_childs = (Liar::Node**)realloc(m_childs, sizeof(Liar::Node*)*(m_numberChild+1));
			for (Liar::Uint i = m_numberChild - 1; m_numberChild == startIndex; --i)
			{
				m_childs[i + 1] = m_childs[i];
			}
			m_childs[startIndex] = node;
		}
		++m_numberChild;
		return node;
	}

	void Node::SpliceChild(Liar::Uint startIndex, bool destroy)
	{
		startIndex = std::min(m_numberChild - 1, startIndex);
		for (Liar::Uint i = m_numberChild - 1; i == startIndex; --i)
		{
			if (destroy) m_childs[i]->~Node();
			m_childs[i] = nullptr;
			free(m_childs[i]);
		}
	}

	/**
	* �����ӽڵ���󣬻�ȡ�ӽڵ������λ�á�
	* @param	node �ӽڵ㡣
	* @return	�ӽڵ����ڵ�����λ�á�
	*/
	Liar::Int Node::GetChildIndex(Liar::Node* node) const
	{
		for (Liar::Uint i = 0; i < m_numberChild; ++i)
		{
			Liar::Node* cur = m_childs[i];
			if (cur == node) return i;
		}

		return -1;
	}

	/**
	* �����ӽڵ������λ�ã���ȡ�ӽڵ����
	* @param	index ����λ��
	* @return	�ӽڵ�
	*/
	Liar::Node* Node::GetChildAt(Liar::Int index)
	{
		if (index < 0 || static_cast<Liar::Uint>(index) >= m_numberChild) return nullptr;
		return m_childs[index];
	}

	/**
	* ɾ���ӽڵ㡣
	* @param	node �ӽڵ�
	* @return	��ɾ���Ľڵ�
	*/
	Liar::Node* Node::RemoveChild(Liar::Node* node)
	{
		if (!m_childs) return node;
		Liar::Int index = GetChildIndex(node);
		return RemoveChildAt(index);
	}

	/**
	* �����ӽڵ�����λ�ã�ɾ����Ӧ���ӽڵ����
	* @param	index �ڵ�����λ�á�
	* @return	��ɾ���Ľڵ㡣
	*/
	Liar::Node* Node::RemoveChildAt(Liar::Int index)
	{
		Liar::Node* node = GetChildAt(index);
		if (node)
		{
			SpliceChild(index, 1, false);
			node->m_parent = nullptr;
		}
		return node;
	}

	/**
	* ɾ��ָ����������������Ӷ���
	* @param	beginIndex ��ʼ������
	* @param	endIndex ����������
	* @return ��ǰ�ڵ����
	*/
	void Node::RemoveChildren(Liar::Int beginIndex, Liar::Int endIndex)
	{
		if (m_childs && m_numberChild > 0)
		{
			beginIndex = std::max(beginIndex, 0);
			endIndex = std::min(endIndex, static_cast<Liar::Int>(m_numberChild));
			for (Liar::Int i = beginIndex; i < endIndex; ++i)
			{
				m_childs[i]->m_parent = nullptr;
			}
			SpliceChild(beginIndex, endIndex, false);
		}
	}

	/**
	* �����ӽڵ㡣
	* @param	node �ڵ����
	* @return	�������ӵĽڵ�
	*/
	Liar::Node* Node::AddChild(Liar::Node* node)
	{
		if (!node || m_destroyed || node == this) return this;
		if (node->m_parent == this)
		{
			Liar::Int index = GetChildIndex(node);
			if (index != m_numberChild - 1)
			{
				SpliceChild(index, 1, false);
				m_childs[m_numberChild - 1] = node;
				ChildChange();
			}
		}
		else
		{
			if (node->m_parent) node->m_parent->RemoveChild(node);
			SpliceChild(m_numberChild, node);
			node->m_parent = this;
			ChildChange();
		}
		return node;
	}

	/**
	* �����ӽڵ㵽ָ��������λ�á�
	* @param	node �ڵ����
	* @param	index ����λ�á�
	* @return	�������ӵĽڵ㡣
	*/
	Liar::Node* Node::AddChildAt(Liar::Node* node, Liar::Int index)
	{
		if (!node || m_destroyed || node == this) return node;
		if (index >= 0 && static_cast<Liar::Uint>(index) < m_numberChild)
		{
			if (node->m_parent == this)
			{
				Liar::Int oldIndex = GetChildIndex(node);
				SpliceChild(oldIndex, 1, false);
				SpliceChild(index, node);
				ChildChange();
			}
			else
			{
				if (node->m_parent) node->m_parent->RemoveChild(node);
				SpliceChild(index, node);
				node->m_parent = this;
			}
			return node;
		}
		return node;
	}

	/**
	* <p>���ٴ˶���destroy����Ĭ�ϻ���Լ��Ӹ��ڵ��Ƴ������������������ù�ϵ���ȴ�js�Զ��������ջ��ƻ��ա�destroy������ʹ�á�</p>
	* <p>destroyʱ���Ƴ����������������������timer�������Ƴ��Ӷ��󼰴Ӹ��ڵ��Ƴ��Լ���</p>
	* @param destroyChild	����ѡ���Ƿ�ͬʱ�����ӽڵ㣬��ֵΪtrue,�������ӽڵ㣬���������ӽڵ㡣
	*/
	bool Node::Destroy(bool destroyChild)
	{
		if (m_destroyed) return false;
		m_destroyed = true;
		if (m_parent) m_parent->RemoveChild(this);
		if (m_childs)
		{
			if (destroyChild) DestroyChildren();
			else RemoveChildren();
			free(m_childs);
		}
		m_childs = nullptr;
		m_parent = nullptr;
		return true;
	}

	/**
	* ���������Ӷ��󣬲������Լ�������
	*/
	void Node::DestroyChildren()
	{
		for (Liar::Uint i = 0; i < m_numberChild; ++i)
		{
			delete m_childs[i];
			m_childs[i] = nullptr;
		}
		m_numberChild = 0;
	}

	/**
	* �Ӹ�����ɾ���Լ������Ѿ���ɾ�������׳��쳣��
	* @return ��ǰ�ڵ㣨 Node ������
	*/
	void Node::RemoveSelf()
	{
		if (m_parent) m_parent->RemoveChild(this);
	}

	/**
	* �����ӽڵ�����֣���ȡ�ӽڵ����
	* @param	name �ӽڵ�����֡�
	* @return	�ڵ����
	*/
	Liar::Node* Node::GetChildByName(const char* name)
	{
		for (Liar::Uint i = 0; i < m_numberChild; ++i)
		{
			Liar::Node* node = m_childs[i];
			if (strcmp(node->m_name, name)) return node;
		}
		return nullptr;
	}

	/**
	* �����ӽڵ�����ɾ����Ӧ���ӽڵ��������Ҳ��������׳��쳣��
	* @param	name �������֡�
	* @return ���ҵ��Ľڵ㣨 Node ������
	*/
	Liar::Node* Node::RemoveChildByName(const char* name)
	{
		Liar::Node* node = GetChildByName(name);
		if (node) RemoveChild(node);
		return node;
	}

	/**
	* �滻�ӽڵ㡣
	* @internal ��������½ڵ�����滻�������ӽڵ�����λ�ô���
	* @param	newNode �½ڵ㡣
	* @param	oldNode �Ͻڵ㡣
	* @return	�����½ڵ㡣
	*/
	Liar::Node* Node::ReplaceChild(Liar::Node* newNode, Liar::Node* oldNode)
	{
		Liar::Int index = GetChildIndex(oldNode);
		if (index > -1)
		{
			m_childs[index] = newNode;
			oldNode->m_parent = nullptr;
			newNode->m_parent = this;
			return newNode;
		}
		return nullptr;
	}

	/**
	* ��ǰ�����Ƿ����ָ���� <code>Node</code> �ڵ���� ��
	* @param	node  ָ���� <code>Node</code> �ڵ���� ��
	* @return	һ������ֵ��ʾ�Ƿ����ָ���� <code>Node</code> �ڵ���� ��
	*/
	bool Node::Contains(Liar::Node* node) const
	{
		if (node == this) return true;
		while (node)
		{
			if (node->m_parent == this) return true;
			node = node->m_parent;
		}
		return false;
	}

	void Node::SetParent(Liar::Node* node)
	{
		if (m_parent != node)
		{
			if (node)
			{
				if (node->GetVisible()) DisplayChild(this, true);
				node->ChildChange(this);
			}
			else
			{
				m_parent->ChildChange();
				if (!node->GetVisible()) DisplayChild(this, false);
			}
			m_parent = node;
		}
	}

	void Node::SetVisible(bool value)
	{
		if (m_visible != value)
		{
			m_visible = value;
		}
	}

	/**
	* @private
	* ����ָ���ڵ�����Ƿ�ɼ�(�Ƿ�����Ⱦ�б���)��
	* @param	node �ڵ㡣
	* @param	display �Ƿ�ɼ���
	*/
	void Node::DisplayChild(Liar::Node* node, bool display)
	{
		if (node)
		{
			for (Liar::Uint i = 0; i < node->m_numberChild; ++i)
			{
				Liar::Node* child = node->m_childs[i];
				if (child->m_numberChild > 0) DisplayChild(child, display);
				else child->SetVisible(display);
			}
			node->SetVisible(display);
		}
	}
}