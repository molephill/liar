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
		Liar::CullTypeDefine m_cull;		/**��Ⱦ�޳�״̬��*/
		Liar::BlendTypeDefine m_blend;			/**͸����ϡ�*/
		Liar::BlendParamDefine m_srcBlend;		/**Դ��ϲ���,��blendΪBLEND_ENABLE_ALLʱ��Ч��*/
		Liar::BlendParamDefine m_dstBlend;		/**Ŀ���ϲ���,��blendΪBLEND_ENABLE_ALLʱ��Ч��*/
		Liar::BlendParamDefine m_srcBlendRGB;	/**RGBԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParamDefine m_dstBlendRGB;	/**RGBԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParamDefine m_srcBlendAlpha;	/**AlphaԴ��ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::BlendParamDefine m_dstBlendAlpha;	/**AlphaĿ���ϲ���,��blendΪBLEND_ENABLE_SEPERATEʱ��Ч��*/
		Liar::Vector4* m_blendConstColor;	/**��ϳ�����ɫ��*/
		Liar::BlendQuationDefine m_blendEquation;	/**��Ϸ��̡�*/
		Liar::BlendQuationDefine m_blendEquationRGB;	/**RGB��Ϸ��̡�*/
		Liar::BlendQuationDefine m_blendEquationAlpha;	/**Alpha��Ϸ��̡�*/
		Liar::DepthTestDefine m_depthTest;			/**��Ȳ��Ժ�����*/
		bool m_depthWrite;				/**�Ƿ����д�롣*/
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
		* ��ȡ͸������ģʽ�ü�ֵ��
		* @return ͸������ģʽ�ü�ֵ��
		*/
		Liar::Number GetAlphaTestValue() const;
		/**
		* ����͸������ģʽ�ü�ֵ��
		* @param value ͸������ģʽ�ü�ֵ��
		*/
		void SetAlphaTestValue(Liar::Number);

		/**
		* ��ȡ�Ƿ�͸���ü���
		* @return �Ƿ�͸���ü���
		*/
		bool GetAlphaTest() const { return m_alphaTest; };
		/**
		* �����Ƿ�͸���ü���
		* @param value �Ƿ�͸���ü���
		*/
		void SetAlphaTest(bool);


		/**
		* ��ȡ����ƽ�̺�ƫ�ơ�
		* @return ����ƽ�̺�ƫ�ơ�
		*/
		Liar::Vector4* GetTilingOffset();
		/**
		* ��ȡ����ƽ�̺�ƫ�ơ�
		* @param value ����ƽ�̺�ƫ�ơ�
		*/
		void SetTilingOffset(Liar::Vector4*);
		/**
		* ���û�������ɫ��
		* @param value ��������ɫ��
		*/
		void SetAmbientColor(Liar::Vector3*);
		Liar::Vector3* GetAmbientColor();
		/**
		* �������������ɫ��
		* @param value ���������ɫ��
		*/
		void SetDiffuseColor(Liar::Vector3*);
		Liar::Vector3* GetDiffuseColor();
		/**
		* ���ø߹���ɫ��
		* @param value �߹���ɫ��
		*/
		void SetSpecularColor(Liar::Vector4*);
		Liar::Vector4* GetSpecularColor();
		/**
		* ���÷�����ɫ��
		* @param value ������ɫ��
		*/
		void SetReflectColor(Liar::Vector3*);
		Liar::Vector3* GetReflectColor();
		/**
		* ���÷����ʡ�
		* @param value �����ʡ�
		*/
		void SetAlbedoColor(Liar::Vector4*);
		Liar::Vector4* GetAlbedoColor();


		/**
		* ��ȡ��������ͼ��
		* @return ��������ͼ��
		*/
		Liar::BaseTexture* GetDiffuseTexture();
		/**
		* ������������ͼ��
		* @param value ��������ͼ��
		*/
		void SetDiffuseTexture(Liar::BaseTexture*);

		/**
		* ��ȡ������ͼ��
		* @return ������ͼ��
		*/
		Liar::BaseTexture* GetNormalTexture();
		/**
		* ���÷�����ͼ��
		* @param value ������ͼ��
		*/
		void SetNormalTexture(Liar::BaseTexture*);

		/**
		* ��ȡ�߹���ͼ��
		* @return �߹���ͼ��
		*/
		Liar::BaseTexture* GetSpecularTexture();
		/**
		* ���ø߹���ͼ��
		* @param value  �߹���ͼ��
		*/
		void SetSpecularTexure(Liar::BaseTexture*);

		/**
		* ��ȡ������ͼ��
		* @return ������ͼ��
		*/
		Liar::BaseTexture* GetEmissiveTexture();
		/**
		* ���÷�����ͼ��
		* @param value ������ͼ��
		*/
		void SetEmissiveTexture(Liar::BaseTexture*);

		/**
		* ��ȡ������ͼ��
		* @return ������ͼ��
		*/
		Liar::BaseTexture* GetAmbientTexture();
		/**
		* ���û�����ͼ��
		* @param  value ������ͼ��
		*/
		void SetAmbientTexture(Liar::BaseTexture*);

		/**
		* ��ȡ������ͼ��
		* @return ������ͼ��
		*/
		Liar::BaseTexture* GetReflectTexture();
		/**
		* ���÷�����ͼ��
		* @param value ������ͼ��
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