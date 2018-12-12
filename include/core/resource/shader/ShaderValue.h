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
		void AddShaderDefine(Liar::ShaderTypeDefine);
		void RemoveShaderDefine(Liar::ShaderTypeDefine);

		Liar::Int GetShaderDefineValue() const { return m_shaderDefineValue; };

		void SetMatrix4x4(Liar::ShaderValueDefine, Liar::Matrix4x4*);
		Liar::Matrix4x4* GetMatrix4x4(Liar::ShaderValueDefine);
		void SetInt(Liar::ShaderValueDefine, Liar::Int);
		int GetInt(Liar::ShaderValueDefine) const;
		void SetFloat(Liar::ShaderValueDefine, Liar::Number);
		float GetFloat(Liar::ShaderValueDefine) const;
		void SetBool(Liar::ShaderValueDefine, bool);
		bool GetBool(Liar::ShaderValueDefine) const;
		void SetVector2(Liar::ShaderValueDefine, Liar::Vector2*);
		Liar::Vector2* GetVector2(Liar::ShaderValueDefine);
		void SetVector3(Liar::ShaderValueDefine, Liar::Vector3*);
		Liar::Vector3* GetVector3(Liar::ShaderValueDefine);
		void SetVector4(Liar::ShaderValueDefine, Liar::Vector4*);
		Liar::Vector4* GetVector4(Liar::ShaderValueDefine);
		void SetColor(Liar::ShaderValueDefine, Liar::Vector3*);
		void SetColor(Liar::ShaderValueDefine, Liar::Vector4*);

	private:
		Liar::Int CalcNumberIndex(Liar::ShaderValueDefine, Liar::Uint&);
	};

}
