
#include <core/material/BaseMaterial.h>
#include <Liar3D.h>

namespace Liar
{
	BaseMaterial::BaseMaterial() :
		Liar::Resource(),
		m_textures(nullptr), m_numberTexture(0),
		m_alphaTest(false),
		m_cull(Liar::CullTypeDefine::CULL_BACK),
		m_blend(Liar::BlendTypeDefine::BLEND_DISABLE),
		m_srcBlend(Liar::BlendParamDefine::BLENDPARAM_ONE), m_dstBlend(Liar::BlendParamDefine::BLENDPARAM_ZERO),
		m_srcBlendRGB(Liar::BlendParamDefine::BLENDPARAM_ONE), m_dstBlendRGB(Liar::BlendParamDefine::BLENDPARAM_ZERO),
		m_srcBlendAlpha(Liar::BlendParamDefine::BLENDPARAM_ONE), m_dstBlendAlpha(Liar::BlendParamDefine::BLENDPARAM_ZERO),
		m_blendConstColor(new Liar::Vector4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_blendEquation(Liar::BlendQuationDefine::BLENDEQUATION_ADD), m_blendEquationRGB(Liar::BlendQuationDefine::BLENDEQUATION_ADD),
		m_blendEquationAlpha(Liar::BlendQuationDefine::BLENDEQUATION_ADD),
		m_depthTest(Liar::DepthTestDefine::DEPTHTEST_LESS),
		m_depthWrite(false), m_renderQueue(Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE),
		m_shaderValues(new Liar::ShaderValue())
	{
	}


	BaseMaterial::~BaseMaterial()
	{
		Destroy();
	}

	void BaseMaterial::RecreateResource()
	{
		Liar::Resource::RecreateResource();
		m_textures = (Liar::BaseTexture**)malloc(sizeof(Liar::BaseTexture*));
		m_numberTexture = 0;
	}

	void BaseMaterial::DisposeResource()
	{
		for (size_t i = 0; i < m_numberTexture; ++i)
		{
			if (m_textures[i])
			{
				m_textures[i]->ReduceRefrence();
				m_textures[i] = nullptr;
			}
		}
		free(m_textures);
		m_textures = nullptr;
	}

	void BaseMaterial::SetTexture(Liar::BaseTexture* texture, size_t index)
	{
		if (!texture) return;
		if (index < 0 || index == m_numberTexture) index = m_numberTexture + 1;
		if (index >= m_numberTexture)
		{
			if(index > 0) m_textures = (Liar::BaseTexture**)realloc(m_textures, sizeof(Liar::BaseTexture*)*index);
			for (size_t i = m_numberTexture; i < index; ++i) m_textures[i] = nullptr;
			m_numberTexture = index;
		}
		else
		{
			m_textures[index]->ReduceRefrence();
			m_textures[index] = nullptr;
		}
		texture->AddRefrence();
		m_textures[index] = texture;
	}

	Liar::BaseTexture* BaseMaterial::GetTexture(size_t index)
	{
		if (index < 0 || index >= m_numberTexture) return nullptr;
		return m_textures[index];
	}

	Liar::Int BaseMaterial::AddRefrence()
	{
		Liar::Int val = Liar::Resource::AddRefrence();
		if (m_textures)
		{
			for (size_t i = 0; i < m_numberTexture; ++i)
			{
				m_textures[i]->AddRefrence();
			}
		}
		return val;
	}

	Liar::Int BaseMaterial::ReduceRefrence()
	{
		Liar::Int val = Liar::Resource::ReduceRefrence();
		if (val > 0 && m_textures)
		{
			for (size_t i = 0; i < m_numberTexture; ++i)
			{
				m_textures[i]->ReduceRefrence();
			}
		}
		return val;
	}

	void BaseMaterial::SetRenderStateBlendDepth()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		gl.SetDepthMask(m_depthTest);
		if (m_depthTest == Liar::DepthTestDefine::DEPTHTEST_OFF)
		{
			gl.SetDepthTest(false);
		}
		else
		{
			gl.SetDepthTest(true);
			gl.SetDepthFunc(m_depthTest);
		}

		switch (m_blend)
		{
		case Liar::BlendTypeDefine::BLEND_DISABLE:
			gl.SetBlend(false);
			break;
		case Liar::BlendTypeDefine::BLEND_ENABLE_ALL:
			gl.SetBlend(true);
			gl.SetBlendFunc(m_srcBlend, m_dstBlend);
			break;
		case Liar::BlendTypeDefine::BLEND_ENABLE_SEPERATE:
			gl.SetBlend(true);
			break;
		default:
			break;
		}
	}

	void BaseMaterial::SetRenderStateFrontFace(bool isTarget, Liar::Transform3D* transform)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		Liar::Int frontFace = 0;
		switch (m_cull)
		{
		case Liar::CullTypeDefine::CULL_NONE:
			gl.SetCullFace(false);
			break;
		case Liar::CullTypeDefine::CULL_FRONT:
		{
			gl.SetFrontFace(true);
			if (isTarget)
			{
				if (transform && transform->IsFrontFaceInvert()) frontFace = GL_CCW;
				else frontFace = GL_CW;
			}
			else
			{
				if (transform && transform->IsFrontFaceInvert()) frontFace = GL_CW;
				else frontFace = GL_CCW;
			}
			gl.SetFrontFace(frontFace);
			break;
		}
		case Liar::CullTypeDefine::CULL_BACK:
		{
			gl.SetCullFace(true);
			if (isTarget)
			{
				if (transform && transform->IsFrontFaceInvert()) frontFace = GL_CW;
				else frontFace = GL_CCW;
			}
			else
			{
				if (transform && transform->IsFrontFaceInvert()) frontFace = GL_CCW;
				else frontFace = GL_CW;
			}
			gl.SetFrontFace(frontFace);
			break;
		}
		default:
			break;
		}
	}

	/**
	* ��ȡ͸������ģʽ�ü�ֵ��
	* @return ͸������ģʽ�ü�ֵ��
	*/
	Liar::Number BaseMaterial::GetAlphaTestValue() const
	{
		return m_shaderValues->GetFloat(Liar::ShaderValueDefine::SHADERVALUE_ALPHATESTVALUE);
	}

	/**
	* ����͸������ģʽ�ü�ֵ��
	* @param value ͸������ģʽ�ü�ֵ��
	*/
	void BaseMaterial::SetAlphaTestValue(Liar::Number value)
	{
		m_shaderValues->SetFloat(Liar::ShaderValueDefine::SHADERVALUE_ALPHATESTVALUE, value);
	}

	/**
	* �����Ƿ�͸���ü���
	* @param value �Ƿ�͸���ü���
	*/
	void BaseMaterial::SetAlphaTest(bool value)
	{
		m_alphaTest = value;
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ALPHATEST) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ALPHATEST);
	}

	/**
	* ��ȡ����ƽ�̺�ƫ�ơ�
	* @return ����ƽ�̺�ƫ�ơ�
	*/
	Liar::Vector4* BaseMaterial::GetTilingOffset()
	{
		return m_shaderValues->GetVector4(Liar::ShaderValueDefine::SHADERVALUE_TILINGOFFSET);
	}

	/**
	* ��ȡ����ƽ�̺�ƫ�ơ�
	* @param value ����ƽ�̺�ƫ�ơ�
	*/
	void BaseMaterial::SetTilingOffset(Liar::Vector4* value)
	{
		if (value)
		{
			if (value->x != 1 || value->y != 1 || value->z != 0 || value->w != 0) m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_TILINGOFFSET);
			else m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_TILINGOFFSET);
		}
		else
		{
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_TILINGOFFSET);
		}
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_TILINGOFFSET, value);
	}

	/**
	* ���û�������ɫ��
	* @param value ��������ɫ��
	*/
	void BaseMaterial::SetAmbientColor(Liar::Vector3* value)
	{
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_MATERIALAMBIENT, value);
	}

	Liar::Vector3* BaseMaterial::GetAmbientColor()
	{
		return m_shaderValues->GetVector3(Liar::ShaderValueDefine::SHADERVALUE_MATERIALAMBIENT);
	}

	/**
	* �������������ɫ��
	* @param value ���������ɫ��
	*/
	void BaseMaterial::SetDiffuseColor(Liar::Vector3* value)
	{
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_MATERIALDIFFUSE, value);
	}

	Liar::Vector3* BaseMaterial::GetDiffuseColor()
	{
		return m_shaderValues->GetVector3(Liar::ShaderValueDefine::SHADERVALUE_MATERIALDIFFUSE);
	}

	/**
	* ���ø߹���ɫ��
	* @param value �߹���ɫ��
	*/
	void BaseMaterial::SetSpecularColor(Liar::Vector4* value)
	{
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_MATERIALSPECULAR, value);
	}

	Liar::Vector4* BaseMaterial::GetSpecularColor()
	{
		return m_shaderValues->GetVector4(Liar::ShaderValueDefine::SHADERVALUE_MATERIALSPECULAR);
	}

	/**
	* ���÷�����ɫ��
	* @param value ������ɫ��
	*/
	void BaseMaterial::SetReflectColor(Liar::Vector3* value)
	{
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_MATERIALREFLECT, value);
	}

	Liar::Vector3* BaseMaterial::GetReflectColor()
	{
		return m_shaderValues->GetVector3(Liar::ShaderValueDefine::SHADERVALUE_MATERIALREFLECT);
	}

	/**
	* ���÷����ʡ�
	* @param value �����ʡ�
	*/
	void BaseMaterial::SetAlbedoColor(Liar::Vector4* value)
	{
		m_shaderValues->SetColor(Liar::ShaderValueDefine::SHADERVALUE_ALBEDO, value);
	}

	Liar::Vector4* BaseMaterial::GetAlbedoColor()
	{
		return m_shaderValues->GetVector4(Liar::ShaderValueDefine::SHADERVALUE_ALBEDO);
	}

	/**
	* ��ȡ��������ͼ��
	* @return ��������ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetDiffuseTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_DIFFUSETEXTURE);
	}

	/**
	* ������������ͼ��
	* @param value ��������ͼ��
	*/
	void BaseMaterial::SetDiffuseTexture(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_DIFFUSEMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_DIFFUSEMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_DIFFUSETEXTURE);
	}

	/**
	* ��ȡ������ͼ��
	* @return ������ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetNormalTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_NORMALTEXTURE);
	}

	/**
	* ���÷�����ͼ��
	* @param value ������ͼ��
	*/
	void BaseMaterial::SetNormalTexture(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_NORMALMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_NORMALMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_NORMALTEXTURE);
	}

	/**
	* ��ȡ�߹���ͼ��
	* @return �߹���ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetSpecularTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_SPECULARTEXTURE);
	}

	/**
	* ���ø߹���ͼ��
	* @param value  �߹���ͼ��
	*/
	void BaseMaterial::SetSpecularTexure(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_SPECULARMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_SPECULARMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_SPECULARTEXTURE);
	}

	/**
	* ��ȡ������ͼ��
	* @return ������ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetEmissiveTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_EMISSIVETEXTURE);
	}

	/**
	* ���÷�����ͼ��
	* @param value ������ͼ��
	*/
	void BaseMaterial::SetEmissiveTexture(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_EMISSIVEMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_EMISSIVEMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_EMISSIVETEXTURE);
	}

	/**
	* ��ȡ������ͼ��
	* @return ������ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetAmbientTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_AMBIENTTEXTURE);
	}

	/**
	* ���û�����ͼ��
	* @param  value ������ͼ��
	*/
	void BaseMaterial::SetAmbientTexture(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_AMBIENTMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_AMBIENTMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_AMBIENTTEXTURE);
	}

	/**
	* ��ȡ������ͼ��
	* @return ������ͼ��
	*/
	Liar::BaseTexture* BaseMaterial::GetReflectTexture()
	{
		return GetTexture(Liar::ShaderValueDefine::SHADERVALUE_REFLECTTEXTURE);
	}

	/**
	* ���÷�����ͼ��
	* @param value ������ͼ��
	*/
	void BaseMaterial::SetReflectTexture(Liar::BaseTexture* value)
	{
		value ? m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_REFLECTMAP) : m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_REFLECTMAP);
		SetTexture(value, Liar::ShaderValueDefine::SHADERVALUE_REFLECTTEXTURE);
	}

	bool BaseMaterial::Destroy()
	{
		bool destroy = Liar::Resource::Destroy();
		if (destroy)
		{
			delete m_blendConstColor;
			m_blendConstColor = nullptr;

			delete m_shaderValues;
			m_shaderValues = nullptr;
		}
		return destroy;
	}
}