
#include <core/resource/ShaderResource.h>

namespace Liar
{
	ShaderResource::ShaderResource():
		m_floatValues(nullptr), m_numberFloat(0),
		m_intValues(nullptr), m_numberInt(0),
		m_boolValues(nullptr), m_numberBool(0),
		m_vec2Values(nullptr), m_numberVec2(0),
		m_vec3Values(nullptr), m_numberVec3(0),
		m_vec4Values(nullptr), m_numberVec4(0),
		m_matrix4x4Values(nullptr), m_numberMatrix4x4(0)
	{
	}


	ShaderResource::~ShaderResource()
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
				//delete m_vec2Values[i];
				m_vec2Values[i] = nullptr;
			}
			free(m_vec2Values);
			m_vec2Values = nullptr;
		}
		if (m_vec3Values)
		{
			for (i = 0; i < m_numberVec3; ++i)
			{
				//delete m_vec3Values[i];
				m_vec3Values[i] = nullptr;
			}
			free(m_vec3Values);
			m_vec3Values = nullptr;
		}
		if (m_vec4Values)
		{
			for (i = 0; i < m_numberVec4; ++i)
			{
				//delete m_vec4Values[i];
				m_vec4Values[i] = nullptr;
			}
			free(m_vec4Values);
			m_vec4Values = nullptr;
		}

		if (m_matrix4x4Values)
		{
			for (i = 0; i < m_numberMatrix4x4; ++i)
			{
				//delete m_matrix4x4Values[i];
				m_matrix4x4Values[i] = nullptr;
			}
			free(m_matrix4x4Values);
			m_matrix4x4Values = nullptr;
		}
	}

	/**
	* ÉèÖÃ¾ØÕó¡£
	* @param	shaderIndex shaderË÷Òý¡£
	* @param	matrix4x4  ¾ØÕó¡£
	*/
	void ShaderResource::SetMatrix4x4(Liar::Uint shaderIndex, const Liar::Matrix4x4& mat)
	{
		Liar::Matrix4x4* temp = new Liar::Matrix4x4(mat);
		Liar::Uint realIndex = shaderIndex;
		if (shaderIndex == m_numberMatrix4x4) ++realIndex;
		else if (shaderIndex > m_numberMatrix4x4) realIndex = shaderIndex + 1;
		if (m_matrix4x4Values)
		{
			if (realIndex > m_numberMatrix4x4)
			{
				m_matrix4x4Values = (Liar::Matrix4x4**)realloc(m_matrix4x4Values, sizeof(Liar::Matrix4x4*)*m_numberMatrix4x4);
			}
		}
		else
		{
			m_matrix4x4Values = (Liar::Matrix4x4**)malloc(sizeof(Liar::Matrix4x4*)*realIndex);
		}
		m_numberMatrix4x4 = realIndex;
		m_matrix4x4Values[shaderIndex] = temp;
	}

}