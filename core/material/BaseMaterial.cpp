
#include <core/material/BaseMaterial.h>

namespace Liar
{
	BaseMaterial::BaseMaterial() :
		Liar::Resource(),
		Liar::ShaderResource(),
		m_textures(nullptr), m_numberTexture(0),
		m_alphaTest(false),
		m_cull(Liar::CullType::CULL_BACK),
		m_blend(Liar::BlendType::BLEND_DISABLE),
		m_srcBlend(Liar::BlendParam::BLENDPARAM_ONE), m_dstBlend(Liar::BlendParam::BLENDPARAM_ZERO),
		m_srcBlendRGB(Liar::BlendParam::BLENDPARAM_ONE), m_dstBlendRGB(Liar::BlendParam::BLENDPARAM_ZERO),
		m_srcBlendAlpha(Liar::BlendParam::BLENDPARAM_ONE), m_dstBlendAlpha(Liar::BlendParam::BLENDPARAM_ZERO),
		m_blendConstColor(new Liar::Vector4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_blendEquation(Liar::BlendQuation::BLENDEQUATION_ADD), m_blendEquationRGB(Liar::BlendQuation::BLENDEQUATION_ADD),
		m_blendEquationAlpha(Liar::BlendQuation::BLENDEQUATION_ADD),
		m_depthTest(Liar::DepthTest::DEPTHTEST_LESS),
		m_depthWrite(false)
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

	bool BaseMaterial::Destroy()
	{
		bool destroy = Liar::Resource::Destroy();
		if (destroy)
		{
			delete m_blendConstColor;
			m_blendConstColor = nullptr;
		}
		return destroy;
	}
}