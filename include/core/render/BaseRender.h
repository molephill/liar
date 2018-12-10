#pragma once

#include <core/resource/Resource.h>
#include <core/resource/shader/ShaderValue.h>
#include <core/material/BaseMaterial.h>
#include <core/display/TransformNode.h>

namespace Liar
{
	class BaseRender :public Liar::Resource
	{
	public:
		BaseRender();
		virtual ~BaseRender();

	protected:
		Liar::ShaderValue* m_shaderValue;
		Liar::TransformNode* m_node;

		bool m_receiveShadow;
		bool m_castShadow;
	};
}