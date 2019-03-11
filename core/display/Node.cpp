#include <core/display/Node.h>
#include <Liar3D.h>

namespace Liar
{
	Node::Node() :
		Liar::EventDispatcher(),
		m_bits(0), m_numberChild(0), m_childs(nullptr),
		m_parent(nullptr), m_name(""),
		m_visible(true), m_transform3D(new Liar::Transform3D())
	{
	}

	Node::~Node()
	{
		if (m_parent) m_parent->RemoveChild(this);
		if (m_childs)
		{
			DestroyChildren();
			free(m_childs);
		}
		m_childs = nullptr;
		m_parent = nullptr;

		delete m_transform3D;
		m_transform3D = nullptr;
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
			if (destroy) delete m_childs[i];
			m_childs[i] = m_childs[replaceIndex++];
		}

		if (destroy)
		{
			replaceIndex = startIndex + len;
			for (Liar::Uint i = replaceIndex; i < max; ++i)
			{
				delete m_childs[i];
				m_childs[i] = nullptr;
			}
		}

		m_numberChild -= (max - startIndex);
	}

	Liar::Node* Node::SpliceChild(Liar::Uint startIndex, Liar::Node* node)
	{
		if (!node) return node;
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
			if (destroy) delete m_childs[i];
			m_childs[i] = nullptr;
			free(m_childs[i]);
		}
	}

	/**
	* 根据子节点对象，获取子节点的索引位置。
	* @param	node 子节点。
	* @return	子节点所在的索引位置。
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
	* 根据子节点的索引位置，获取子节点对象。
	* @param	index 索引位置
	* @return	子节点
	*/
	Liar::Node* Node::GetChildAt(Liar::Int index)
	{
		if (index < 0 || static_cast<Liar::Uint>(index) >= m_numberChild) return nullptr;
		return m_childs[index];
	}

	/**
	* 删除子节点。
	* @param	node 子节点
	* @return	被删除的节点
	*/
	Liar::Node* Node::RemoveChild(Liar::Node* node)
	{
		if (!m_childs) return node;
		Liar::Int index = GetChildIndex(node);
		return RemoveChildAt(index);
	}

	/**
	* 根据子节点索引位置，删除对应的子节点对象。
	* @param	index 节点索引位置。
	* @return	被删除的节点。
	*/
	Liar::Node* Node::RemoveChildAt(Liar::Int index)
	{
		Liar::Node* node = GetChildAt(index);
		if (node)
		{
			SpliceChild(index, 1, false);
			node->SetParent(nullptr);
		}
		return node;
	}

	/**
	* 删除指定索引区间的所有子对象。
	* @param	beginIndex 开始索引。
	* @param	endIndex 结束索引。
	* @return 当前节点对象。
	*/
	void Node::RemoveChildren(Liar::Int beginIndex, Liar::Int endIndex)
	{
		if (m_childs && m_numberChild > 0)
		{
			beginIndex = std::max(beginIndex, 0);
			endIndex = std::min(endIndex, static_cast<Liar::Int>(m_numberChild));
			for (Liar::Int i = beginIndex; i < endIndex; ++i)
			{
				m_childs[i]->SetParent(nullptr);
			}
			SpliceChild(beginIndex, endIndex, false);
		}
	}

	/**
	* 添加子节点。
	* @param	node 节点对象
	* @return	返回添加的节点
	*/
	Liar::Node* Node::AddChild(Liar::Node* node)
	{
		if (!node || node == this) return this;
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
			node->SetParent(this);
			ChildChange();
		}
		return node;
	}

	/**
	* 添加子节点到指定的索引位置。
	* @param	node 节点对象。
	* @param	index 索引位置。
	* @return	返回添加的节点。
	*/
	Liar::Node* Node::AddChildAt(Liar::Node* node, Liar::Int index)
	{
		if (!node || node == this) return node;
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
				node->SetParent(this);
			}
			return node;
		}
		return node;
	}

	/**
	* 销毁所有子对象，不销毁自己本身。
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
	* 从父容器删除自己，如已经被删除不会抛出异常。
	* @return 当前节点（ Node ）对象。
	*/
	void Node::RemoveSelf()
	{
		if (m_parent) m_parent->RemoveChild(this);
	}

	/**
	* 根据子节点的名字，获取子节点对象。
	* @param	name 子节点的名字。
	* @return	节点对象。
	*/
	Liar::Node* Node::GetChildByName(const char* name)
	{
		for (Liar::Uint i = 0; i < m_numberChild; ++i)
		{
			Liar::Node* node = m_childs[i];
			if (strcmp((node->m_name).c_str(), name)) return node;
		}
		return nullptr;
	}

	/**
	* 根据子节点名字删除对应的子节点对象，如果找不到不会抛出异常。
	* @param	name 对象名字。
	* @return 查找到的节点（ Node ）对象。
	*/
	Liar::Node* Node::RemoveChildByName(const char* name)
	{
		Liar::Node* node = GetChildByName(name);
		if (node) RemoveChild(node);
		return node;
	}

	/**
	* 替换子节点。
	* @internal 将传入的新节点对象替换到已有子节点索引位置处。
	* @param	newNode 新节点。
	* @param	oldNode 老节点。
	* @return	返回新节点。
	*/
	Liar::Node* Node::ReplaceChild(Liar::Node* newNode, Liar::Node* oldNode)
	{
		Liar::Int index = GetChildIndex(oldNode);
		if (index > -1)
		{
			m_childs[index] = newNode;
			oldNode->SetParent(nullptr);
			newNode->SetParent(this);
			return newNode;
		}
		return nullptr;
	}

	/**
	* 当前容器是否包含指定的 <code>Node</code> 节点对象 。
	* @param	node  指定的 <code>Node</code> 节点对象 。
	* @return	一个布尔值表示是否包含指定的 <code>Node</code> 节点对象 。
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
				m_transform3D->SetParent(node->m_transform3D);
				if (node->GetVisible()) DisplayChild(this, true);
				node->ChildChange(this);
			}
			else
			{
				m_transform3D->SetParent(nullptr);
				m_parent->ChildChange();
				DisplayChild(this, false);
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
	* 设置指定节点对象是否可见(是否在渲染列表中)。
	* @param	node 节点。
	* @param	display 是否可见。
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

	Liar::RenderUnit* Node::GetRenderUint(Liar::RenderState& state)
	{
		Liar::RenderUnit* unit = Liar::Liar3D::rendering->PopRenderUnit();
		m_transform3D->CalclateTransformation(&(state.camera->GetProjectionViewMatrix()));
		unit->transform = m_transform3D;
		return unit;
	}

	Liar::Int Node::CollectRenderUint(Liar::RenderState& state)
	{
		Liar::Liar3D::rendering->AddRenderUnit(GetRenderUint(state));
		return CollectChildrenRenderUint(state) + 1;
	}

	Liar::Int Node::CollectChildrenRenderUint(Liar::RenderState& state)
	{
		Liar::Int count = 0;
		for (size_t i = 0; i < m_numberChild; ++i)
		{
			count += m_childs[i]->CollectRenderUint(state);
		}
		return count;
	}

}
