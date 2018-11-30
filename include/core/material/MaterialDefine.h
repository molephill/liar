#pragma once

namespace Liar
{
	enum CullType
	{
		/**剔除枚举_不剔除。*/
		CULL_NONE = 0,
		/**剔除枚举_剔除正面。*/
		CULL_FRONT,
		/**剔除枚举_剔除背面。*/
		CULL_BACK
	};

	enum BlendType
	{
		/**混合枚举_禁用。*/
		BLEND_DISABLE = 0,
		/**混合枚举_启用_RGB和Alpha统一混合。*/
		BLEND_ENABLE_ALL,
		/**混合枚举_启用_RGB和Alpha单独混合。*/
		BLEND_ENABLE_SEPERATE
	};

	/*混合参数枚举*/
	enum BlendParam
	{
		/**混合参数枚举_零,例：RGB(0,0,0),Alpha:(1)。*/
		BLENDPARAM_ZERO = 0,
		/**混合参数枚举_一,例：RGB(1,1,1),Alpha:(1)。*/
		BLENDPARAM_ONE = 1,
		/**混合参数枚举_源颜色,例：RGB(Rs, Gs, Bs)，Alpha(As)。*/
		BLENDPARAM_SRC_COLOR = 0x0300,
		/**混合参数枚举_一减源颜色,例：RGB(1-Rs, 1-Gs, 1-Bs)，Alpha(1-As)。*/
		BLENDPARAM_ONE_MINUS_SRC_COLOR = 0x0301,
		/**混合参数枚举_源透明,例:RGB(As, As, As),Alpha(1-As)。*/
		BLENDPARAM_SRC_ALPHA = 0x0302,
		/**混合参数枚举_一减源阿尔法,例:RGB(1-As, 1-As, 1-As),Alpha(1-As)。*/
		BLENDPARAM_ONE_MINUS_SRC_ALPHA = 0x0303,
		/**混合参数枚举_目标阿尔法，例：RGB(Ad, Ad, Ad),Alpha(Ad)。*/
		BLENDPARAM_DST_ALPHA = 0x0304,
		/**混合参数枚举_一减目标阿尔法,例：RGB(1-Ad, 1-Ad, 1-Ad),Alpha(Ad)。*/
		BLENDPARAM_ONE_MINUS_DST_ALPHA = 0x0305,
		/**混合参数枚举_目标颜色,例：RGB(Rd, Gd, Bd),Alpha(Ad)。*/
		BLENDPARAM_DST_COLOR = 0x0306,
		/**混合参数枚举_一减目标颜色,例：RGB(1-Rd, 1-Gd, 1-Bd)，Alpha(1-Ad)。*/
		BLENDPARAM_ONE_MINUS_DST_COLOR = 0x0307,
		/**混合参数枚举_阿尔法饱和，例：RGB(min(As, 1 - Ad), min(As, 1 - Ad), min(As, 1 - Ad)),Alpha(1)。*/
		BLENDPARAM_SRC_ALPHA_SATURATE = 0x0308
	};

	/*混合方程枚举*/
	enum BlendQuation
	{
		/**混合方程枚举_加法,例：source + destination*/
		BLENDEQUATION_ADD,
		/**混合方程枚举_减法，例：source - destination*/
		BLENDEQUATION_SUBTRACT,
		/**混合方程枚举_反序减法，例：destination - source*/
		BLENDEQUATION_REVERSE_SUBTRACT
	};

	/*深度测试函数枚举*/
	enum DepthTest
	{
		/**深度测试函数枚举_关闭深度测试。*/
		DEPTHTEST_OFF,
		/**深度测试函数枚举_从不通过。*/
		DEPTHTEST_NEVER = 0x0200,
		/**深度测试函数枚举_小于时通过。*/
		DEPTHTEST_LESS,
		/**深度测试函数枚举_等于时通过。*/
		DEPTHTEST_EQUAL,
		/**深度测试函数枚举_小于等于时通过。*/
		DEPTHTEST_LEQUAL,
		/**深度测试函数枚举_大于时通过。*/
		DEPTHTEST_GREATER,
		/**深度测试函数枚举_不等于时通过。*/
		DEPTHTEST_NOTEQUAL,
		/**深度测试函数枚举_大于等于时通过。*/
		DEPTHTEST_GEQUAL,
		/**深度测试函数枚举_总是通过。*/
		DEPTHTEST_ALWAYS
	};
}