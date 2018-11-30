#pragma once

#include <core/resource/BaseTexture.h>
#include <core/resource/Resource.h>
#include <core/material/MaterialDefine.h>
#include <core/resource/ShaderResource.h>

namespace Liar
{
	class BaseMaterial:public Liar::Resource,public Liar::ShaderResource
	{
	public:
		BaseMaterial();
		virtual ~BaseMaterial();

	protected:
		Liar::BaseTexture** m_textures;
		Liar::Uint m_numberTexture;

		bool m_alphaTest;

	protected:
		virtual void DisposeResource();
		virtual void RecreateResource();

	protected:
		Liar::CullType m_cull;		/**渲染剔除状态。*/
		Liar::BlendType m_blend;			/**透明混合。*/
		Liar::BlendParam m_srcBlend;		/**源混合参数,在blend为BLEND_ENABLE_ALL时生效。*/
		Liar::BlendParam m_dstBlend;		/**目标混合参数,在blend为BLEND_ENABLE_ALL时生效。*/
		Liar::BlendParam m_srcBlendRGB;	/**RGB源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParam m_dstBlendRGB;	/**RGB源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParam m_srcBlendAlpha;	/**Alpha源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParam m_dstBlendAlpha;	/**Alpha目标混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::Vector4* m_blendConstColor;	/**混合常量颜色。*/
		Liar::BlendQuation m_blendEquation;	/**混合方程。*/
		Liar::BlendQuation m_blendEquationRGB;	/**RGB混合方程。*/
		Liar::BlendQuation m_blendEquationAlpha;	/**Alpha混合方程。*/
		Liar::DepthTest m_depthTest;			/**深度测试函数。*/
		bool m_depthWrite;				/**是否深度写入。*/

	public:
		virtual void SetTexture(Liar::BaseTexture*, size_t index = -1);
		Liar::BaseTexture* GetTexture(size_t);

		virtual Liar::Int AddRefrence();
		virtual Liar::Int ReduceRefrence();
		virtual bool Destroy();
	};
}