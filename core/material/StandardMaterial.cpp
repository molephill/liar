#include <core/material/StandardMaterial.h>

namespace Liar
{
	StandardMaterial::StandardMaterial():
		Liar::BaseMaterial()
	{
	}


	StandardMaterial::~StandardMaterial()
	{
	}

	void StandardMaterial::SetRenderMode(Liar::RenderModeDefine value)
	{
		switch (value)
		{
		case Liar::RenderModeDefine::RENDERMODE_OPAQUE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_DISABLE;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_OPAQUEDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_DISABLE;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_CUTOUT:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_alphaTest = true;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_CUTOUTDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_OPAQUE;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_alphaTest = true;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_TRANSPARENT:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_TRANSPARENTDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_ADDTIVE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_ADDTIVEDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = true;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_DEPTHREAD_TRANSPARENT:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = false;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_DEPTHREAD_TRANSPARENTDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = false;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_DEPTHREAD_ADDTIVE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = false;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_DEPTHREAD_ADDTIVEDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthWrite = false;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_NONDEPTH_TRANSPARENT:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthTest = Liar::DepthTestDefine::DEPTHTEST_LESS;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_NONDEPTH_TRANSPARENTDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthTest = Liar::DepthTestDefine::DEPTHTEST_LESS;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE_MINUS_SRC_ALPHA;
			m_alphaTest = false;
			m_shaderValues->RemoveShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_NONDEPTH_ADDTIVE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthTest = Liar::DepthTestDefine::DEPTHTEST_LESS;
			m_cull = Liar::CullTypeDefine::CULL_BACK;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		case Liar::RenderModeDefine::RENDERMODE_NONDEPTH_ADDTIVEDOUBLEFACE:
		{
			m_renderQueue = Liar::RenderQueueDefine::RENDERQUEUE_TRANSPARENT;
			m_depthTest = Liar::DepthTestDefine::DEPTHTEST_LESS;
			m_cull = Liar::CullTypeDefine::CULL_NONE;
			m_blend = Liar::BlendTypeDefine::BLEND_ENABLE_ALL;
			m_srcBlend = Liar::BlendParamDefine::BLENDPARAM_SRC_ALPHA;
			m_dstBlend = Liar::BlendParamDefine::BLENDPARAM_ONE;
			m_alphaTest = false;
			m_shaderValues->AddShaderDefine(Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG);
			break;
		}
		default:
			break;
		}
	}
}
