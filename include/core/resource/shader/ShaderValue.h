#pragma once

#include <math/Vector2.h>
#include <math/Matrix4x4.h>
#include <core/resource/shader/ShaderDefine.h>

namespace Liar
{
	class ShaderValue
	{
	public:
		ShaderValue();
		~ShaderValue();

	protected:
		Liar::Number* m_floatValues;		/* float 定义值*/
		Liar::Uint m_numberFloat;			/* float 数量 */

		Liar::Int* m_intValues;
		Liar::Uint m_numberInt;

		bool* m_boolValues;
		Liar::Uint m_numberBool;

		Liar::Vector2** m_vec2Values;
		Liar::Uint m_numberVec2;

		Liar::Vector3** m_vec3Values;
		Liar::Uint m_numberVec3;

		Liar::Vector4** m_vec4Values;
		Liar::Uint m_numberVec4;

		Liar::Matrix4x4** m_matrix4x4Values;
		Liar::Uint m_numberMatrix4x4;

		Liar::Int m_shaderDefineValue;

	public:
		virtual void AddShaderDefine(Liar::ShaderTypeDefine);
		virtual void RemoveShaderDefine(Liar::ShaderTypeDefine);
		virtual void SetMatrix4x4(Liar::ShaderValueDefine, Liar::Matrix4x4*);
		virtual Liar::Matrix4x4* GetMatrix4x4(Liar::ShaderValueDefine);
		virtual void SetInt(Liar::ShaderValueDefine, Liar::Int);
		virtual int GetInt(Liar::ShaderValueDefine) const;
		virtual void SetFloat(Liar::ShaderValueDefine, Liar::Number);
		virtual float GetFloat(Liar::ShaderValueDefine) const;
		virtual void SetBool(Liar::ShaderValueDefine, bool);
		virtual bool GetBool(Liar::ShaderValueDefine) const;
		virtual void SetVector2(Liar::ShaderValueDefine, Liar::Vector2*);
		virtual Liar::Vector2* GetVector2(Liar::ShaderValueDefine);
		virtual void SetVector3(Liar::ShaderValueDefine, Liar::Vector3*);
		virtual Liar::Vector3* GetVector3(Liar::ShaderValueDefine);
		virtual void SetVector4(Liar::ShaderValueDefine, Liar::Vector4*);
		virtual Liar::Vector4* GetVector4(Liar::ShaderValueDefine);
		virtual void SetColor(Liar::ShaderValueDefine, Liar::Vector3*);
		virtual void SetColor(Liar::ShaderValueDefine, Liar::Vector4*);

	private:
		Liar::Int CalcNumberIndex(Liar::ShaderValueDefine, Liar::Uint&);
	};

}
