#pragma once

#include <core/display/TransformNode.h>

namespace Liar
{
	TransformNode::TransformNode():
		Liar::Node(),
		m_transform3D(new Liar::Transform3D()),
		m_material(nullptr)
	{
	}

	TransformNode::~TransformNode()
	{
		Destroy();
	}

	bool TransformNode::Destroy(bool destroyChild)
	{
		bool destroied = Liar::Node::Destroy(destroyChild);
		if (destroied)
		{
			delete m_transform3D;
			m_transform3D = nullptr;

			if (m_material)
			{
				m_material->ReduceRefrence();
				m_material = nullptr;
			}
		}
		return destroied;
	}

	bool TransformNode::Render(Liar::StageContext& gl, Liar::RenderState& state)
	{
		m_transform3D->CalclateTransformation();
		return true;
	}
}