#pragma once

#include "Transform3D.h"
#include <core/material/BaseMaterial.h>
#include <core/display/EventDispatcher.h>
#include <core/render/RenderUnit.h>
#include <core/render/RenderState.h>
#include <core/resource/shader/ShaderProgram.h>
#include <core/resource/shader/ShaderCompile.h>
#include <LiarType.h>

namespace Liar
{
	class Node:public EventDispatcher
	{
	public:
		Node();
		virtual ~Node();

	protected:
		int m_bits;
		Liar::Node** m_childs;
		Liar::Uint m_numberChild;
		Liar::Node* m_parent;
		std::string m_name;
		bool m_visible;
		Liar::Transform3D* m_transform3D;
		Liar::ShaderProgram* m_shaderProgram;
		Liar::PreCompileShader* m_preCompileShader;

	public:
		virtual void SetUpNoticeType(int);
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

		void SetName(const char* name) { m_name = name; };

	protected:
		virtual void ChildChange(Liar::Node* child = nullptr) {};
		virtual Liar::RenderUnit* GetRenderUint(Liar::RenderState&, bool buildShader = false);
		virtual bool BuildShaderProgram(Liar::RenderState&);

	public:
		inline bool GetBit(int type) const { return (m_bits & type) != 0; };
		inline void SetBit(int type, bool value) { if (value) m_bits |= type; else m_bits &= ~type; };
		Liar::Node* GetParent() const { return m_parent; };
		virtual Liar::Uint NumChildren() const { return m_numberChild; };
		bool GetVisible() const { return m_visible; };
		virtual Liar::Int CollectRenderUint(Liar::RenderState&, bool buildShader = false);
		virtual Liar::Int CollectChildrenRenderUint(Liar::RenderState&, bool buildShader = true);
		Liar::Transform3D& GetTransform3D() { return *m_transform3D; };

	private:
		void DisplayChild(Liar::Node*, bool);
	};
} 

