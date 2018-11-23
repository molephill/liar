#pragma once

#include "Node.h"
#include "Transform3D.h"

namespace Liar
{
	class TransformNode :public Node
	{
	public:
		TransformNode();
		virtual ~TransformNode();

	protected:
		Liar::Transform3D* m_transform3D;
		bool m_transformChanged;

	public:
		Liar::Transform3D& GetTransform3D() const { return *m_transform3D; };
		bool GetTransformChanged() const { return m_transformChanged || m_transform3D->GetTransformChanged(); };

		virtual bool Destroy(bool destroyChild = true);
	};
}