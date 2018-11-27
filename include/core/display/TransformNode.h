#pragma once

#include "Node.h"
#include "Transform3D.h"
#include <core/render/RenderState.h>
#include <core/render/StageContext.h>

namespace Liar
{
	class TransformNode :public Node
	{
	public:
		TransformNode();
		virtual ~TransformNode();

	protected:
		Liar::Transform3D* m_transform3D;

	protected:
		virtual void CalculateProjectionMatrix();

	public:
		Liar::Transform3D& GetTransform3D() const { return *m_transform3D; };
		virtual bool GetTransformChanged() const { return m_transform3D->GetTransformChanged(); };

		virtual bool Render(Liar::StageContext& gl, Liar::RenderState& state);
		virtual bool Destroy(bool destroyChild = true);
	};
}