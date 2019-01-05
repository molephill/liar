
#include <core/light/DirectionLight.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	DirectionLight::DirectionLight():
		Liar::BaseLight(),
		m_direction(new Liar::Vector3())
	{
	}

	DirectionLight::~DirectionLight()
	{
		delete m_direction;
		m_direction = nullptr;
	}

	bool DirectionLight::PrepareRender(Liar::RenderState& state)
	{
		if (state.enableLight)
		{
			state.shaderValue->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_DIRECTIONLIGHT);
			m_transform3d->CalclateTransformation(&(state.camera->GetProjectionViewMatrix()));
			m_transform3d->GetWorldMatrix().GetForward(*m_direction);
			m_direction->Normalize();
			state.shaderValue->SetVector3(Liar::ShaderValueDefine::SHADERVALUE_LIGHTDIRECTION, m_direction);
			return true;
		}
		else
		{
			state.shaderValue->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_DIRECTIONLIGHT);
			return false;
		}
	}
}