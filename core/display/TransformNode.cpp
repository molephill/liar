#pragma once

#include <core/display/TransformNode.h>

namespace Liar
{
	TransformNode::TransformNode():
		Liar::Node(),
		m_transform3D(new Liar::Transform3D()),
		m_transformChanged(true)
	{
	}

	TransformNode::~TransformNode()
	{

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
}