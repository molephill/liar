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
		Liar::CullType m_cull;		/**��Ⱦ�޳�״̬��*/
		Liar::BlendType m_blend;			/**͸����ϡ�*/
		Liar::BlendParam m_srcBlend;		/**Դ��ϲ���,��blendΪBLEND_ENABLE_ALLʱ��Ч��*/
		Liar::BlendParam m_dstBlend;		/**Ŀ���ϲ���,��blendΪBLEND_ENABLE_ALLʱ��Ч��*/
		Liar::BlendParam m_srcBlendRGB;	/**RGBԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParam m_dstBlendRGB;	/**RGBԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParam m_srcBlendAlpha;	/**AlphaԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParam m_dstBlendAlpha;	/**AlphaĿ���ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::Vector4* m_blendConstColor;	/**��ϳ�����ɫ��*/
		Liar::BlendQuation m_blendEquation;	/**��Ϸ��̡�*/
		Liar::BlendQuation m_blendEquationRGB;	/**RGB��Ϸ��̡�*/
		Liar::BlendQuation m_blendEquationAlpha;	/**Alpha��Ϸ��̡�*/
		Liar::DepthTest m_depthTest;			/**��Ȳ��Ժ�����*/
		bool m_depthWrite;				/**�Ƿ����д�롣*/

	public:
		virtual void SetTexture(Liar::BaseTexture*, size_t index = -1);
		Liar::BaseTexture* GetTexture(size_t);

		virtual Liar::Int AddRefrence();
		virtual Liar::Int ReduceRefrence();
		virtual bool Destroy();
	};
}