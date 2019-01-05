
#include <core/light/PointLight.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	PointLight::PointLight() :
		Liar::BaseLight(),
		m_range(6.0f)
	{
	}

	PointLight::~PointLight()
	{
		
	}

	bool PointLight::PrepareRender(Liar::RenderState& state)
	{
		if (state.enableLight)
		{
			state.shaderValue->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_POINTLIGHT);
			Liar::Vector3* tmp = &(Liar::MathUtils3D::TEMPVector30);
			m_transform3d->CalclateTransformation(&(state.camera->GetProjectionViewMatrix()));
			Liar::Matrix4x4& worldMatrix = m_transform3d->GetWorldMatrix();
			tmp->Set(worldMatrix[12], worldMatrix[13], worldMatrix[14]);
			state.shaderValue->SetVector3(Liar::ShaderValueDefine::SHADERVALUE_POINTLIGHTPOS, tmp);
			state.shaderValue->SetFloat(Liar::ShaderValueDefine::SHADERVALUE_POINTLIGHTRANGE, m_range);
			return true;
		}
		else
		{
			state.shaderValue->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_POINTLIGHT);
			return false;
		}
	}
}