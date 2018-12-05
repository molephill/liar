#pragma once

namespace Liar
{
	enum ShaderTypeDefine
	{
		SHADERTYPE_ALPHATEST,
		SHADERTYPE_DIFFUSEMAP,
		SHADERTYPE_NORMALMAP,
		SHADERTYPE_SPECULARMAP,
		SHADERTYPE_EMISSIVEMAP,
		SHADERTYPE_AMBIENTMAP,
		SHADERTYPE_REFLECTMAP,
		SHADERTYPE_UVTRANSFORM,
		SHADERTYPE_TILINGOFFSET,
		SHADERTYPE_ADDTIVEFOG,
		SHADERTYPE_HIGHPRECISION,
		SHADERTYPE_FOG,
		SHADERTYPE_DIRECTIONLIGHT,
		SHADERTYPE_POINTLIGHT,
		SHADERTYPE_SPOTLIGHT,
		SHADERTYPE_UV0,
		SHADERTYPE_COLOR,
		SHADERTYPE_UV1,
		SHADERTYPE_DEPTHFOG
	};

	enum ShaderValueDefine
	{
		/**着色器变量,透明测试值。*/
		SHADERVALUE_ALPHATESTVALUE,
		SHADERVALUE_DIFFUSETEXTURE,
		SHADERVALUE_NORMALTEXTURE,
		SHADERVALUE_SPECULARTEXTURE,
		SHADERVALUE_EMISSIVETEXTURE,
		SHADERVALUE_AMBIENTTEXTURE,
		SHADERVALUE_REFLECTTEXTURE,
		SHADERVALUE_ALBEDO,
		SHADERVALUE_UVANIAGE,
		SHADERVALUE_MATERIALAMBIENT,
		SHADERVALUE_MATERIALDIFFUSE,
		SHADERVALUE_MATERIALSPECULAR,
		SHADERVALUE_MATERIALREFLECT,
		SHADERVALUE_UVMATRIX,
		SHADERVALUE_UVAGE,
		SHADERVALUE_TILINGOFFSET
	};
}