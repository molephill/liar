
#include <core/resource/shader/ShaderValue.h>

namespace Liar
{
	ShaderValue::ShaderValue():
		m_floatValues(nullptr), m_numberFloat(0),
		m_intValues(nullptr), m_numberInt(0),
		m_boolValues(nullptr), m_numberBool(0),
		m_vec2Values(nullptr), m_numberVec2(0),
		m_vec3Values(nullptr), m_numberVec3(0),
		m_vec4Values(nullptr), m_numberVec4(0),
		m_matrix4x4Values(nullptr), m_numberMatrix4x4(0),
		m_shaderDefineValue(0)
	{
	}


	ShaderValue::~ShaderValue()
	{
		size_t i = 0;
		if (m_floatValues) free(m_floatValues);
		m_floatValues = nullptr;
		if (m_intValues) free(m_intValues);
		m_intValues = nullptr;
		if (m_boolValues)free(m_boolValues);
		if (m_vec2Values)
		{
			for (i = 0; i < m_numberVec2; ++i)
			{
				if (m_vec2Values[i])
				{
					delete m_vec2Values[i];
					m_vec2Values[i] = nullptr;
				}
			}
			free(m_vec2Values);
			m_vec2Values = nullptr;
		}
		if (m_vec3Values)
		{
			for (i = 0; i < m_numberVec3; ++i)
			{
				if (m_vec3Values[i])
				{
					delete m_vec3Values[i];
					m_vec3Values[i] = nullptr;
				}
			}
			free(m_vec3Values);
			m_vec3Values = nullptr;
		}
		if (m_vec4Values)
		{
			for (i = 0; i < m_numberVec4; ++i)
			{
				if (m_vec4Values[i])
				{
					delete m_vec4Values[i];
					m_vec4Values[i] = nullptr;
				}
			}
			free(m_vec4Values);
			m_vec4Values = nullptr;
		}

		if (m_matrix4x4Values)
		{
			for (i = 0; i < m_numberMatrix4x4; ++i)
			{
				if (m_matrix4x4Values[i])
				{
					delete m_matrix4x4Values[i];
					m_matrix4x4Values[i] = nullptr;
				}
			}
			free(m_matrix4x4Values);
			m_matrix4x4Values = nullptr;
		}
	}

	/*
	* �����µĳ���
	*/
	Liar::Int ShaderValue::CalcNumberIndex(Liar::ShaderValueDefine shaderIndex1, Liar::Uint& numberIndex)
	{
		Liar::Uint shaderIndex = static_cast<Liar::Uint>(shaderIndex1);
		Liar::Uint preIndex = numberIndex;
		Liar::Uint realIndex = shaderIndex;
		if (shaderIndex == numberIndex) ++realIndex;
		else if (shaderIndex > numberIndex) realIndex = shaderIndex + 1;
		numberIndex = realIndex;
		return preIndex;
	}

	/**
	* ����Shader�궨�塣
	* @param value �궨�塣
	*/
	void ShaderValue::AddShaderDefine(Liar::ShaderTypeDefine value)
	{
		m_shaderDefineValue |= value;
	}

	/**
	* �Ƴ�Shader�궨�塣
	* @param value �궨�塣
	*/
	void ShaderValue::RemoveShaderDefine(Liar::ShaderTypeDefine value)
	{
		m_shaderDefineValue &= ~value;
	}

	/**
	* ��ȡ����
	* @param	shaderIndex shader������
	* @return  ����
	*/
	Liar::Matrix4x4* ShaderValue::GetMatrix4x4(Liar::ShaderValueDefine shaderIndex)
	{
		return static_cast<Liar::Uint>(shaderIndex) < m_numberMatrix4x4 ? m_matrix4x4Values[shaderIndex] : nullptr;
	}

	/**
	* �������͡�
	* @param	shaderIndex shader������
	* @param	i ���Ρ�
	*/
	void ShaderValue::SetInt(Liar::ShaderValueDefine shaderIndex, Liar::Int value)
	{
		Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberInt);
		if (m_intValues)
		{
			if (m_numberInt > preIndex) m_intValues = (Liar::Int*)realloc(m_intValues, sizeof(Liar::Int)*m_numberInt);
		}
		else
		{
			m_intValues = (Liar::Int*)malloc(sizeof(Liar::Int)*m_numberInt);
		}
		m_intValues[shaderIndex] = value;
	}

	/**
	* ��ȡ���Ρ�
	* @param	shaderIndex shader������
	* @return  ���Ρ�
	*/
	Liar::Int ShaderValue::GetInt(Liar::ShaderValueDefine shaderIndex) const
	{
		return m_intValues[shaderIndex];
	}


	/**
	* ���ø��㡣
	* @param	shaderIndex shader������
	* @param	i ���㡣
	*/
	void ShaderValue::SetFloat(Liar::ShaderValueDefine shaderIndex, Liar::Number value)
	{
		Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberFloat);
		if (m_floatValues)
		{
			if (m_numberFloat > preIndex) m_floatValues = (Liar::Number*)realloc(m_floatValues, sizeof(Liar::Number)*m_numberFloat);
		}
		else
		{
			m_floatValues = (Liar::Number*)malloc(sizeof(Liar::Number)*m_numberFloat);
		}
		m_floatValues[shaderIndex] = value;
	}

	/**
	* ��ȡ���㡣
	* @param	shaderIndex shader������
	* @return  ���㡣
	*/
	Liar::Number ShaderValue::GetFloat(Liar::ShaderValueDefine shaderIndex) const
	{
		return m_floatValues[shaderIndex];
	}

	/**
	* ���ò�����
	* @param	shaderIndex shader������
	* @param	b ������
	*/
	void ShaderValue::SetBool(Liar::ShaderValueDefine shaderIndex, bool value)
	{
		Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberBool);
		if (m_boolValues)
		{
			if (m_numberBool > preIndex) m_boolValues = (bool*)realloc(m_boolValues, sizeof(bool)*m_numberBool);
		}
		else
		{
			m_boolValues = (bool*)malloc(sizeof(bool)*m_numberBool);
		}
		m_boolValues[shaderIndex] = value;
	}

	/**
	* ��ȡ������
	* @param	shaderIndex shader������
	* @return  ������
	*/
	bool ShaderValue::GetBool(Liar::ShaderValueDefine shaderIndex) const
	{
		return m_boolValues[shaderIndex];
	}

	/**
	* ���þ���
	* @param	shaderIndex shader������
	* @param	matrix4x4  ����
	*/
	void ShaderValue::SetMatrix4x4(Liar::ShaderValueDefine shaderIndex, Liar::Matrix4x4* mat)
	{
		if (mat)
		{
			Liar::Matrix4x4* temp = new Liar::Matrix4x4(*mat);
			Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberMatrix4x4);
			if (m_matrix4x4Values)
			{
				if (m_numberMatrix4x4 > preIndex)
				{
					m_matrix4x4Values = (Liar::Matrix4x4**)realloc(m_matrix4x4Values, sizeof(Liar::Matrix4x4*)*m_numberMatrix4x4);
				}
			}
			else
			{
				m_matrix4x4Values = (Liar::Matrix4x4**)malloc(sizeof(Liar::Matrix4x4*)*m_numberMatrix4x4);
			}
			m_matrix4x4Values[shaderIndex] = temp;
		}
		else
		{
			if (static_cast<Liar::Uint>(shaderIndex) < m_numberMatrix4x4)
			{
				if (m_matrix4x4Values[shaderIndex]) delete m_matrix4x4Values[shaderIndex];
				m_matrix4x4Values[shaderIndex] = nullptr;
			}
		}
	}

	/**
	* ���ö�ά������
	* @param	shaderIndex shader������
	* @param	vector2 ��ά������
	*/
	void ShaderValue::SetVector2(Liar::ShaderValueDefine shaderIndex, Liar::Vector2* value)
	{
		if (value)
		{
			Liar::Vector2* tmp = new Liar::Vector2(*value);
			Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberVec2);
			if (m_vec2Values)
			{
				if (m_numberVec2 > preIndex) m_vec2Values = (Liar::Vector2**)realloc(m_vec2Values, sizeof(Liar::Vector2*)*m_numberVec2);
			}
			else
			{
				m_vec2Values = (Liar::Vector2**)malloc(sizeof(Liar::Vector2*)*m_numberVec2);
			}
			m_vec2Values[shaderIndex] = tmp;
		}
		else
		{
			if (static_cast<Liar::Uint>(shaderIndex) < m_numberVec2)
			{
				if (m_vec2Values[shaderIndex]) delete m_vec2Values[shaderIndex];
				m_vec2Values[shaderIndex] = nullptr;
			}
		}
	}

	/**
	* ��ȡ��ά������
	* @param	shaderIndex shader������
	* @return ��ά������
	*/
	Liar::Vector2* ShaderValue::GetVector2(Liar::ShaderValueDefine shaderIndex)
	{
		return static_cast<Liar::Uint>(shaderIndex) < m_numberVec2 ? m_vec2Values[shaderIndex] : nullptr;
	}

	/**
	* ������ά������
	* @param	shaderIndex shader������
	* @param	vector3 ��ά������
	*/
	void ShaderValue::SetVector3(Liar::ShaderValueDefine shaderIndex, Liar::Vector3* value)
	{
		if (value)
		{
			Liar::Vector3* tmp = new Liar::Vector3(*value);
			Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberVec3);
			if (m_vec3Values)
			{
				if (m_numberVec3 > preIndex) m_vec3Values = (Liar::Vector3**)realloc(m_vec3Values, sizeof(Liar::Vector3*)*m_numberVec3);
			}
			else
			{
				m_vec3Values = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*)*m_numberVec3);
			}
			m_vec3Values[shaderIndex] = tmp;
		}
		else
		{
			if (static_cast<Liar::Uint>(shaderIndex) < m_numberVec3)
			{
				if (m_vec3Values[shaderIndex]) delete m_vec3Values[shaderIndex];
				m_vec3Values[shaderIndex] = nullptr;
			}
		}
	}

	/**
	* ��ȡ��ά������
	* @param	shaderIndex shader������
	* @return ��ά������
	*/
	Liar::Vector3* ShaderValue::GetVector3(Liar::ShaderValueDefine shaderIndex)
	{
		return static_cast<Liar::Uint>(shaderIndex) < m_numberVec3 ? m_vec3Values[shaderIndex] : nullptr;
	}

	/**
	* ������ά������
	* @param	shaderIndex shader������
	* @param	vector4 ��ά������
	*/
	void ShaderValue::SetVector4(Liar::ShaderValueDefine shaderIndex, Liar::Vector4* value)
	{
		if (value)
		{
			Liar::Vector4* tmp = new Liar::Vector4(*value);
			Liar::Uint preIndex = CalcNumberIndex(shaderIndex, m_numberVec4);
			if (m_vec4Values)
			{
				if (m_numberVec4 > preIndex) m_vec4Values = (Liar::Vector4**)realloc(m_vec4Values, sizeof(Liar::Vector4*)*m_numberVec4);
			}
			else
			{
				m_vec4Values = (Liar::Vector4**)malloc(sizeof(Liar::Vector4*)*m_numberVec4);
			}
			m_vec4Values[shaderIndex] = tmp;
		}
		else
		{
			if (shaderIndex < m_numberVec4)
			{
				if (m_vec4Values[shaderIndex]) delete m_vec4Values[shaderIndex];
				m_vec4Values[shaderIndex] = nullptr;
			}
		}
	}

	/**
	* ��ȡ��ά������
	* @param	shaderIndex shader������
	* @return ��ά������
	*/
	Liar::Vector4* ShaderValue::GetVector4(Liar::ShaderValueDefine shaderIndex)
	{
		return shaderIndex < m_numberVec4 ? m_vec4Values[shaderIndex] : nullptr;
	}

	/**
	* ������ɫ��
	*/
	void ShaderValue::SetColor(Liar::ShaderValueDefine shaderIndex, Liar::Vector3* rhs)
	{
		SetVector3(shaderIndex, rhs);
	}

	void ShaderValue::SetColor(Liar::ShaderValueDefine shaderIndex, Liar::Vector4* rhs)
	{
		SetVector4(shaderIndex, rhs);
	}
}