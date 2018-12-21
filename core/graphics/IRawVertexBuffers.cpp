#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <Liar3D.h>

namespace Liar
{
	IRawVertexBuffers::IRawVertexBuffers():
		m_indices(nullptr), m_numberIndices(0),
		m_vertexKeys(nullptr), m_numberVertexKeys(0)
	{
	}

	IRawVertexBuffers::~IRawVertexBuffers()
	{
		Destroy();
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

	void IRawVertexBuffers::UploadData(GLenum type)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t indicesSize = sizeof(Liar::Uint)*m_numberIndices;
		gl.BufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_indices, GL_STATIC_DRAW);
	}

	void IRawVertexBuffers::Destroy()
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
	}
}