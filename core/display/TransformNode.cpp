#pragma once

#include <core/display/TransformNode.h>

namespace Liar
{
	TransformNode::TransformNode():
		Liar::Node(),
		m_transform3D(new Liar::Transform3D())
	{
	}

	TransformNode::~TransformNode()
	{
		delete m_transform3D;
		m_transform3D = nullptr;
	}

	bool TransformNode::Destroy(bool destroyChild)
	{
		bool destroied = Liar::Node::Destroy(destroyChild);
		if (destroied)
		{
			delete m_transform3D;
			m_transform3D = nullptr;
		}
		return destroied;
	}

	void TransformNode::CalculateProjectionMatrix()
	{
		m_transform3D->CalclateTransformation();
	}

	bool TransformNode::Render(Liar::StageContext& gl, Liar::RenderState& state)
	{
		CalculateProjectionMatrix();
		return true;
	}
}