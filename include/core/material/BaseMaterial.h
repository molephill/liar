#pragma once

#include <core/resource/BaseTexture.h>
#include <core/resource/Resource.h>
#include <core/material/MaterialDefine.h>
#include <core/resource/shader/ShaderValue.h>
#include <core/display/Transform3D.h>
#include <core/render/RenderDefine.h>

namespace Liar
{
	class BaseMaterial:public Liar::Resource
	{
	public:
		BaseMaterial();
		virtual ~BaseMaterial();

	protected:
		std::string m_name;
		Liar::BaseTexture** m_textures;
		Liar::Uint m_numberTexture;
		bool m_alphaTest;

	protected:
		virtual void DisposeResource();
		virtual void RecreateResource();

	protected:
		Liar::CullTypeDefine m_cull;		/**渲染剔除状态。*/
		Liar::BlendTypeDefine m_blend;			/**透明混合。*/
		Liar::BlendParamDefine m_srcBlend;		/**源混合参数,在blend为BLEND_ENABLE_ALL时生效。*/
		Liar::BlendParamDefine m_dstBlend;		/**目标混合参数,在blend为BLEND_ENABLE_ALL时生效。*/
		Liar::BlendParamDefine m_srcBlendRGB;	/**RGB源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParamDefine m_dstBlendRGB;	/**RGB源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParamDefine m_srcBlendAlpha;	/**Alpha源混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::BlendParamDefine m_dstBlendAlpha;	/**Alpha目标混合参数,在blend为BLEND_ENABLE_SEPERATE时生效。*/
		Liar::Vector4* m_blendConstColor;	/**混合常量颜色。*/
		Liar::BlendQuationDefine m_blendEquation;	/**混合方程。*/
		Liar::BlendQuationDefine m_blendEquationRGB;	/**RGB混合方程。*/
		Liar::BlendQuationDefine m_blendEquationAlpha;	/**Alpha混合方程。*/
		Liar::DepthTestDefine m_depthTest;			/**深度测试函数。*/
		bool m_depthWrite;				/**是否深度写入。*/
		Liar::RenderQueueDefine m_renderQueue;
		Liar::ShaderValue* m_shaderValues;

	public:
		void SetCull(Liar::CullTypeDefine type) { m_cull = type; };
		Liar::CullTypeDefine GetCull() const { return m_cull; };
		void SetBlend(Liar::BlendTypeDefine type) { m_blend = type; };
		Liar::BlendTypeDefine GetBlend() const { return m_blend; };
		void SetSrcBlend(Liar::BlendParamDefine type) { m_srcBlend = type; };
		Liar::BlendParamDefine GetSrcBlend() const { return m_srcBlend; };
		void SetDstBlend(Liar::BlendParamDefine type) { m_dstBlend = type; };
		Liar::BlendParamDefine GetDstBlend() const { return m_dstBlend; };
		void SetSrcBlendRGB(Liar::BlendParamDefine type) { m_srcBlendRGB = type; };
		Liar::BlendParamDefine GetSrcBlendRGB() const { return m_srcBlendRGB; };
		void SetDstBlendRGB(Liar::BlendParamDefine type) { m_dstBlendRGB = type; };
		Liar::BlendParamDefine GetDstBlendRGB() const { return m_dstBlendRGB; };
		void SetSrcBlendAlpha(Liar::BlendParamDefine type) { m_srcBlendAlpha = type; };
		Liar::BlendParamDefine GetSrcBlendAlpha() const { return m_srcBlendAlpha; };
		void SetDstBlendAlpha(Liar::BlendParamDefine type) { m_dstBlendAlpha = type; };
		Liar::BlendParamDefine GetDstBlendAlpha() const { return m_dstBlendAlpha; };
		void SetBlendConstColor(float r, float g, float b, float a) { m_blendConstColor->Set(r, g, b, a); };
		void SetBlendConstColor(const Liar::Vector4& rhs) { m_blendConstColor->Set(rhs); };
		Liar::Vector4& GetBlendConstColor() const { return *m_blendConstColor; };
		void SetBlendEuqation(Liar::BlendQuationDefine type) { m_blendEquation = type; };
		Liar::BlendQuationDefine GetBlendEquation() const { return m_blendEquation; };
		void SetBlendEquationRGB(Liar::BlendQuationDefine type) { m_blendEquationRGB = type; };
		Liar::BlendQuationDefine GetBlendEquationRGB() const { return m_blendEquationRGB; };
		void SetBlendEquationAlpha(Liar::BlendQuationDefine type) { m_blendEquationAlpha = type; };
		Liar::BlendQuationDefine GetBlendEquationAlpha() const { return m_blendEquationAlpha; };
		void SetDepthTest(Liar::DepthTestDefine type) { m_depthTest = type; };
		Liar::DepthTestDefine GetDepthTest() const { return m_depthTest; };
		void SetDepthWrite(bool value) { m_depthWrite = value; };
		bool GetDepthWrite() const { return m_depthWrite; };
		void SetRenderQueue(Liar::RenderQueueDefine type) { m_renderQueue = type; };
		Liar::RenderQueueDefine GetRenderQueue() const { return m_renderQueue; };
		Liar::ShaderValue& GetShaderValue() { return *m_shaderValues; };
		std::string GetName() const { return m_name; };
		void SetName(const char* name) { m_name = name; };
		Liar::Uint GetNumberTexture() const { return m_numberTexture; };
		bool Equals(const char* name) const { return m_name == name; };

	public:
		/**
		* 获取透明测试模式裁剪值。
		* @return 透明测试模式裁剪值。
		*/
		Liar::Number GetAlphaTestValue() const;
		/**
		* 设置透明测试模式裁剪值。
		* @param value 透明测试模式裁剪值。
		*/
		void SetAlphaTestValue(Liar::Number);

		/**
		* 获取是否透明裁剪。
		* @return 是否透明裁剪。
		*/
		bool GetAlphaTest() const { return m_alphaTest; };
		/**
		* 设置是否透明裁剪。
		* @param value 是否透明裁剪。
		*/
		void SetAlphaTest(bool);


		/**
		* 获取纹理平铺和偏移。
		* @return 纹理平铺和偏移。
		*/
		Liar::Vector4* GetTilingOffset();
		/**
		* 获取纹理平铺和偏移。
		* @param value 纹理平铺和偏移。
		*/
		void SetTilingOffset(Liar::Vector4*);
		/**
		* 设置环境光颜色。
		* @param value 环境光颜色。
		*/
		void SetAmbientColor(Liar::Vector3*);
		Liar::Vector3* GetAmbientColor();
		/**
		* 设置漫反射光颜色。
		* @param value 漫反射光颜色。
		*/
		void SetDiffuseColor(Liar::Vector3*);
		Liar::Vector3* GetDiffuseColor();
		/**
		* 设置高光颜色。
		* @param value 高光颜色。
		*/
		void SetSpecularColor(Liar::Vector4*);
		Liar::Vector4* GetSpecularColor();
		/**
		* 设置反射颜色。
		* @param value 反射颜色。
		*/
		void SetReflectColor(Liar::Vector3*);
		Liar::Vector3* GetReflectColor();
		/**
		* 设置反射率。
		* @param value 反射率。
		*/
		void SetAlbedoColor(Liar::Vector4*);
		Liar::Vector4* GetAlbedoColor();


		/**
		* 获取漫反射贴图。
		* @return 漫反射贴图。
		*/
		Liar::BaseTexture* GetDiffuseTexture();
		/**
		* 设置漫反射贴图。
		* @param value 漫反射贴图。
		*/
		void SetDiffuseTexture(Liar::BaseTexture*);

		/**
		* 获取法线贴图。
		* @return 法线贴图。
		*/
		Liar::BaseTexture* GetNormalTexture();
		/**
		* 设置法线贴图。
		* @param value 法线贴图。
		*/
		void SetNormalTexture(Liar::BaseTexture*);

		/**
		* 获取高光贴图。
		* @return 高光贴图。
		*/
		Liar::BaseTexture* GetSpecularTexture();
		/**
		* 设置高光贴图。
		* @param value  高光贴图。
		*/
		void SetSpecularTexure(Liar::BaseTexture*);

		/**
		* 获取放射贴图。
		* @return 放射贴图。
		*/
		Liar::BaseTexture* GetEmissiveTexture();
		/**
		* 设置放射贴图。
		* @param value 放射贴图。
		*/
		void SetEmissiveTexture(Liar::BaseTexture*);

		/**
		* 获取环境贴图。
		* @return 环境贴图。
		*/
		Liar::BaseTexture* GetAmbientTexture();
		/**
		* 设置环境贴图。
		* @param  value 环境贴图。
		*/
		void SetAmbientTexture(Liar::BaseTexture*);

		/**
		* 获取反射贴图。
		* @return 反射贴图。
		*/
		Liar::BaseTexture* GetReflectTexture();
		/**
		* 设置反射贴图。
		* @param value 反射贴图。
		*/
		void SetReflectTexture(Liar::BaseTexture*);


	protected:
		virtual void SetTexture(Liar::BaseTexture*, size_t index = -1);


	public:
		Liar::BaseTexture* GetTexture(size_t);
		void SetRenderStateBlendDepth();
		void SetRenderStateFrontFace(bool, Liar::Transform3D* transform = nullptr);

		virtual Liar::Int AddRefrence();
		virtual Liar::Int ReduceRefrence();
		virtual bool Destroy();

		virtual void SetRenderMode(Liar::RenderModeDefine) = 0;
	};
}