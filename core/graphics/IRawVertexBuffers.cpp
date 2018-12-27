#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <Liar3D.h>

namespace Liar
{
	IRawVertexBuffers::IRawVertexBuffers(Liar::GeometryVertexType vertextype) :
		m_geomtryVertexType(vertextype),
		m_indices(nullptr), m_numberIndices(0),
		m_vertexKeys(nullptr), m_numberVertexKeys(0),
		m_mtlIndices(nullptr), m_numberMTLIndices(0)
	{
	}

	IRawVertexBuffers::~IRawVertexBuffers()
	{
		if (m_indices) free(m_indices);
		for (Liar::Int i = 0; i < m_numberVertexKeys; ++i)
		{
			if (m_vertexKeys[i])
			{
				delete m_vertexKeys[i];
				m_vertexKeys[i] = nullptr;
			}
		}
		if (m_vertexKeys) free(m_vertexKeys);
		m_vertexKeys = nullptr;
		
		if (m_mtlIndices) free(m_mtlIndices);
		m_mtlIndices = nullptr;
	}

	void* IRawVertexBuffers::GetVertexBuffer(Liar::VertexElementAttr attr, void** buffers, size_t len, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		void* out = nullptr;
		for (size_t i = 0; i < len; ++i)
		{
			void* buffer = buffers[i];
			switch (attr)
			{
			case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			{
				Liar::Vector3* vec3 = static_cast<Liar::Vector3*>(buffer);
				if (vec3 && vec3->Equal(x, y, z)) return buffer;
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			{
				Liar::Vector2* vec2 = static_cast<Liar::Vector2*>(buffer);
				if (vec2 && vec2->Equal(x, y)) return buffer;
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			{
				Liar::Quaternion* qua = static_cast<Liar::Quaternion*>(buffer);
				if (qua && qua->Equal(x, y, z, w)) return buffer;
				break;
			}
			}
		}

		return out;
	}

	void IRawVertexBuffers::SetIndicesLength(Liar::Int len)
	{
		m_numberIndices = len;
		m_indices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberIndices);
	}

	void IRawVertexBuffers::SetIndex(Liar::Int index, Liar::Uint indices)
	{
		m_indices[index] = indices;
	}

	void IRawVertexBuffers::SetVertexKeyLength(Liar::Int len)
	{
		m_numberVertexKeys = len;
		m_vertexKeys = (Liar::IVertexKey**)malloc(sizeof(Liar::IVertexKey*)*len);
	}

	void IRawVertexBuffers::SetVertexKey(Liar::Int index, Liar::IVertexKey* key)
	{
		m_vertexKeys[index] = key;
	}

	Liar::Int IRawVertexBuffers::GetBufferSize() const
	{
		return GetStride() * m_numberVertexKeys;
	}

	void* IRawVertexBuffers::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		Liar::IVertexKey* key = m_vertexKeys[index];
		Liar::Int vertexIndex = key->GetVertexIndex(attr);
		return GetSubVertexBuffer(attr, vertexIndex);
	}

	/*
	* 不知数据长度时推入
	*/
	void IRawVertexBuffers::PushIndices(Liar::Uint index)
	{
		++m_numberIndices;
		if (m_indices) m_indices = (Liar::Uint*)realloc(m_indices, sizeof(Liar::Uint)*m_numberIndices);
		else m_indices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberIndices);
		m_indices[m_numberIndices - 1] = index;
	}

	void IRawVertexBuffers::PushVertexKey(Liar::IVertexKey* key)
	{
		++m_numberVertexKeys;
		if (m_vertexKeys) m_vertexKeys = (Liar::IVertexKey**)realloc(m_vertexKeys, sizeof(Liar::IVertexKey*)*m_numberVertexKeys);
		else m_vertexKeys = (Liar::IVertexKey**)malloc(sizeof(Liar::IVertexKey*)*m_numberVertexKeys);
		m_vertexKeys[m_numberVertexKeys - 1] = key;
	}

	void IRawVertexBuffers::CheckAddVertexKey(const Liar::IVertexKey& check)
	{
		Liar::IVertexKey* tmpKey = nullptr;
		Liar::Int findIndex = m_numberIndices;
		for (Liar::Int i = 0; i < m_numberVertexKeys; ++i)
		{
			Liar::IVertexKey& hasKey = *(m_vertexKeys[i]);
			if (hasKey == check)
			{
				tmpKey = m_vertexKeys[i];
				findIndex = i;
				break;
			}
		}
		if (!tmpKey)
		{
			tmpKey = check.Clone();
			PushVertexKey(tmpKey);
		}
		PushIndices(findIndex);
	}

	void IRawVertexBuffers::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
		{
			m_numberVertexKeys = len;
			m_vertexKeys = (Liar::IVertexKey**)malloc(sizeof(Liar::IVertexKey*)*m_numberVertexKeys);
			break;
		}
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES:
		{
			m_numberIndices = len;
			m_indices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberIndices);
			break;
		}
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_MTL_INDICES:
		{
			m_numberMTLIndices = len;
			m_mtlIndices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberMTLIndices);
			break;
		}
		default:
			break;
		}
	}

	void IRawVertexBuffers::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
		{
			IVertexKey* key = Liar::Liar3D::geometryFactory->GetVertexFactory().GetVertexKey(m_geomtryVertexType);
			key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, static_cast<Liar::Uint>(x));
			key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, static_cast<Liar::Uint>(y));
			key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, static_cast<Liar::Uint>(z));
			key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, static_cast<Liar::Uint>(w));
			m_vertexKeys[index] = key;
			break;
		}
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES:
			m_indices[index] = static_cast<Liar::Uint>(x);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_MTL_INDICES:
			m_mtlIndices[index] = static_cast<Liar::Uint>(x);
			break;
		default:
			break;
		}
	}

	void IRawVertexBuffers::UploadData(GLenum type)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t indicesSize = sizeof(Liar::Uint)*m_numberIndices;
		gl.BufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_indices, GL_STATIC_DRAW);

		// 提交具体数据
		UploadSubData(type);

		// 绑定
		VertexAttrbPointer();
	}

}