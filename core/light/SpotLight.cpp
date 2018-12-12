
#include <core/light/SpotLight.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	SpotLight::SpotLight():
		Liar::PointLight(),
		m_direction(new Liar::Vector3()),
		m_spot(96.0f)
	{
		m_range = 6.0f;
	}

	SpotLight::~SpotLight()
	{
		Destroy();
	}

	bool SpotLight::PrepareRender(Liar::RenderState& state)
	{
		if (state.enableLight)
		{
			state.shaderValue->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_SPOTLIGHT);
			Liar::Vector3* tmp = &(Liar::MathUtils3D::TEMPVector30);
			m_transform3d->CalclateTransformation(state.camera->GetProjectionViewMatrix());
			Liar::Matrix4x4& worldMatrix = m_transform3d->GetWorldMatrix();
			tmp->Set(worldMatrix[12], worldMatrix[13], worldMatrix[14]);
			state.shaderValue->SetVector3(Liar::ShaderValueDefine::SHADERVALUE_SPOTLIGHTPOS, tmp);
			state.shaderValue->SetFloat(Liar::ShaderValueDefine::SHADERVALUE_SPOTLIGHTRANGE, m_range);
			state.shaderValue->SetFloat(Liar::ShaderValueDefine::SHADERVALUE_SPOTLIGHTSPOT, m_spot);

			m_transform3d->GetWorldMatrix().GetForward(*m_direction);
			m_direction->Normalize();
			state.shaderValue->SetVector3(Liar::ShaderValueDefine::SHADERVALUE_SPOTLIGHTDIRECTION, m_direction);
			return true;
		}
		else
		{
			state.shaderValue->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_SPOTLIGHT);
			return false;
		}
	}

	bool SpotLight::Destroy(bool destroyChild)
	{
		bool destroied = Liar::PointLight::Destroy(destroyChild);
		if (destroied)
		{
			delete m_direction;
			m_direction = nullptr;
		}
		return destroied;
	}
}