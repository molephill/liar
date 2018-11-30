#pragma once

#include <math/Vector2.h>
#include <math/Matrix4x4.h>

namespace Liar
{
	class ShaderResource
	{
	public:
		ShaderResource();
		~ShaderResource();

	protected:
		Liar::DNumber* m_floatValues;		/* float 定义值*/
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

	public:
		void SetMatrix4x4(Liar::Uint, const Liar::Matrix4x4&);
		Liar::Matrix4x4* GetMatrix4x4(Liar::Uint);
		void SetInt(Liar::Uint, int);
		int GetInt(Liar::Uint);
		void SetFloat(Liar::Uint, float);
		float GetFloat(Liar::Uint);
		void SetBool(Liar::Uint, bool);
		bool GetBool(Liar::Uint);
		void SetVector2(Liar::Uint, Liar::Vector2*);
		Liar::Vector2* GetVecto2(Liar::Uint);
		void SetVector3(Liar::Uint, Liar::Vector3*);
		Liar::Vector3* GetVector3(Liar::Uint);
		void SetVector4(Liar::Uint, Liar::Vector4*);
		Liar::Vector4* GetVector4(Liar::Uint);
	};

}
