
#include <core/resource/shader/ShaderCompile.h>

namespace Liar
{
	ShaderCompile::ShaderCompile()
	{
	}


	ShaderCompile::~ShaderCompile()
	{
	}

	const char* ShaderCompile::GetShaderDefineChar(Liar::ShaderTypeDefine type) const
	{
		switch (type)
		{
		case Liar::ShaderTypeDefine::SHADERTYPE_ALPHATEST:
			return "ALPHATEST";
		case Liar::ShaderTypeDefine::SHADERTYPE_DIFFUSEMAP:
			return "DIFFUSEMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_NORMALMAP:
			return "NORMALMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_SPECULARMAP:
			return "SPECULARMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_EMISSIVEMAP:
			return "EMISSIVEMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_REFLECTMAP:
			return "REFLECTMAP";
		case Liar::ShaderTypeDefine::SHADERTYPE_UVTRANSFORM:
			return "UVTRANSFORM";
		case Liar::ShaderTypeDefine::SHADERTYPE_TILINGOFFSET:
			return "TILINGOFFSET";
		case Liar::ShaderTypeDefine::SHADERTYPE_ADDTIVEFOG:
			return "ADDTIVEFOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_HIGHPRECISION:
			return "HIGHPRECISION";
		case Liar::ShaderTypeDefine::SHADERTYPE_FOG:
			return "FOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_DIRECTIONLIGHT:
			return "DIRECTIONLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_POINTLIGHT:
			return "POINTLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_SPOTLIGHT:
			return "SPOTLIGHT";
		case Liar::ShaderTypeDefine::SHADERTYPE_UV0:
			return "UV0";
		case Liar::ShaderTypeDefine::SHADERTYPE_COLOR:
			return "COLOR";
		case Liar::ShaderTypeDefine::SHADERTYPE_UV1:
			return "UV1";
		case Liar::ShaderTypeDefine::SHADERTYPE_DEPTHFOG:
			return "DEPTHFOG";
		case Liar::ShaderTypeDefine::SHADERTYPE_RECEIVE_SHADOW:
			return "RECEIVE_SHADOW";
		case Liar::ShaderTypeDefine::SHADERTYPE_CAST_SHADOW:
			return "CAST_SHADOW";
		default:
			return nullptr;
		}
	}
}
