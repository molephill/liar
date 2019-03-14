#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <Liar3D.h>

namespace Liar
{
	void IVertexKey::SetVertexIndex(Liar::VertexElementAttr type, Liar::Uint val)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			SetPositionIndex(val);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			SetNormalIndex(val);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			SetTexCoordIndex(val);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			SetColorIndex(val);
			break;
		default:
			break;
		}
	}

	Liar::Uint IVertexKey::GetVertexIndex(Liar::VertexElementAttr type) const
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			return GetPositionIndex();
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			return GetNormalIndex();
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			return GetTexCoordIndex();
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			return GetColorIndex();
		/*case Liar::ELEMENT_ATTR_ROTATION:
			break;
		case Liar::ELEMENT_ATTR_RAW_KEY:
			break;
		case Liar::ELEMENT_ATTR_RAW_INDICES:
			break;*/
		default:
			return 0;
		}
	}

	/*
	* 具体数据处理
	*/
	IRawVertexBuffers::IRawVertexBuffers(Liar::GeometryVertexType vertextype) :
		m_geomtryVertexType(vertextype),
		m_indices(nullptr), m_numberIndices(0),
		m_vertexKeys(nullptr), m_numberVertexKeys(0),
		m_mtlIndex(-1)
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
			AddRawKeyVertexBuffer(tmpKey);
		}
		AddRawIndex(findIndex);
	}

	// 获得一个 raw_key 对象
	IVertexKey* IRawVertexBuffers::CreateVertexKey(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		IVertexKey* key = Liar::Liar3D::geometryFactory->GetVertexFactory().GetVertexKey(m_geomtryVertexType);
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, static_cast<Liar::Uint>(x));
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, static_cast<Liar::Uint>(y));
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, static_cast<Liar::Uint>(z));
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_COLOR, static_cast<Liar::Uint>(w));
		return key;
	}

	// 设置raw_key长度
	void IRawVertexBuffers::SetRawKeyVertexBufferLen(Liar::Int len)
	{
		m_numberVertexKeys = len;
		size_t blockSize = sizeof(Liar::IVertexKey*)*m_numberVertexKeys;
		if (m_vertexKeys) m_vertexKeys = (Liar::IVertexKey**)realloc(m_vertexKeys, blockSize);
		else m_vertexKeys = (Liar::IVertexKey**)malloc(blockSize);
	}

	// 设置raw_indexraw_index
	void IRawVertexBuffers::SetRawIndexLen(Liar::Int len)
	{
		m_numberIndices = len;
		size_t blockSize = sizeof(Liar::Uint)*m_numberIndices;
		if (m_indices) m_indices = (Liar::Uint*)realloc(m_indices, blockSize);
		else m_indices = (Liar::Uint*)malloc(blockSize);
	}

	// 增加raw_key信息
	void IRawVertexBuffers::AddRawKeyVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		Liar::IVertexKey* key = CreateVertexKey(x, y, z, w);
		AddRawKeyVertexBuffer(key);
	}

	void IRawVertexBuffers::AddRawKeyVertexBuffer(Liar::IVertexKey* key)
	{
		if (!key) return;
		SetRawKeyVertexBufferLen(m_numberVertexKeys + 1);
		m_vertexKeys[m_numberVertexKeys - 1] = key;
	}

	// 设置raw_key信息
	void IRawVertexBuffers::SetRawKeyVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		Liar::IVertexKey* key = CreateVertexKey(x, y, z, w);
		SetRawKeyVertexBuffer(index, key);
	}

	void IRawVertexBuffers::SetRawKeyVertexBuffer(size_t index, Liar::IVertexKey* key)
	{
		m_vertexKeys[index] = key;
	}

	// 获得raw_key信息
	void* IRawVertexBuffers::GetRawKeyVertexBuffer(Liar::Int index) const
	{
		if (index >= m_numberVertexKeys) return nullptr;
		return m_vertexKeys[index];
	}

	// 增加raw_index信息
	void IRawVertexBuffers::AddRawIndex(Liar::Int x)
	{
		SetRawIndexLen(m_numberIndices + 1);
		m_indices[m_numberIndices - 1] = static_cast<Liar::Uint>(x);
	}

	// 设置raw_index信息
	void IRawVertexBuffers::SetRawIndex(size_t index, Liar::Number x)
	{
		m_indices[index] = static_cast<Liar::Uint>(x);
	}

	// 获得raw_index信息
	void* IRawVertexBuffers::GetRawIndex(size_t index) const
	{
		return &(m_indices[index]);
	}

	void IRawVertexBuffers::AddSubVertexBuffer(Liar::VertexElementAttr type, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			AddPositionVertexBuffer(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			AddNormalVertexBuffer(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			AddTexCoordVertexBuffer(x, y, z);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			AddColorVertexBuffer(x, y, z, w);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			AddRotationVertexBuffer(x, y, z, w);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
			AddRawKeyVertexBuffer(x, y, z, w);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES:
			AddRawIndex(x);
			break;
		default:
			break;
		}
	}

	void IRawVertexBuffers::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			SetPositionVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			SetNormalVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			SetTexCoordVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			SetColorVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			SetRotationVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
			SetRawKeyVertexBufferLen(len);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES:
			SetRawIndexLen(len);
			break;
		default:
			break;
		}
	}

	void IRawVertexBuffers::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index,
		Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		switch (attr)
		{
		case Liar::ELEMENT_ATTR_POSITION:
			SetPositionVertexBuffer(index, x, y, z);
			break;
		case Liar::ELEMENT_ATTR_NORMAL:
			SetNormalVertexBuffer(index, x, y, z);
			break;
		case Liar::ELEMENT_ATTR_TEXTURECOORDINATE:
			SetTexCoordVertexBuffer(index, x, y, z);
			break;
		case Liar::ELEMENT_ATTR_COLOR:
			SetColorVertexBuffer(index, x, y, z, w);
			break;
		case Liar::ELEMENT_ATTR_ROTATION:
			SetRotationVertexBuffer(index, x, y, z, w);
			break;
		case Liar::ELEMENT_ATTR_RAW_KEY:
			SetRawKeyVertexBuffer(index, x, y, z, w);
			break;
		case Liar::ELEMENT_ATTR_RAW_INDICES:
			SetRawIndex(index, x);
			break;
		default:
			break;
		}
	}

	void* IRawVertexBuffers::GetSubVertexBuffer(Liar::VertexElementAttr attr, size_t index)
	{
		switch (attr)
		{
		case Liar::ELEMENT_ATTR_POSITION:
			return GetPostionVertexBuffer(index);
		case Liar::ELEMENT_ATTR_NORMAL:
			return GetNormalVertexBuffer(index);
		case Liar::ELEMENT_ATTR_TEXTURECOORDINATE:
			return GetTexCoordVertexBuffer(index);
		case Liar::ELEMENT_ATTR_COLOR:
			return GetColorVertexBuffer(index);
		case Liar::ELEMENT_ATTR_ROTATION:
			return GetRotationVertexBuffer(index);
		case Liar::ELEMENT_ATTR_RAW_KEY:
			return GetRawKeyVertexBuffer(index);
		case Liar::ELEMENT_ATTR_RAW_INDICES:
			return GetRawIndex(index);
		default:
			return nullptr;
		}
	}

	void IRawVertexBuffers::UploadData(GLenum type)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t indicesSize = sizeof(Liar::Uint)*m_numberIndices;
		gl.BufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_indices, GL_STATIC_DRAW);

		// 提交具体数据
		Liar::Int stride = GetStride();
		for (Liar::Int i = 0; i < m_numberVertexKeys; ++i)
		{
			size_t start = i * stride;
			LoopUploadSubData(gl, type, i, start);
		}

		// 绑定
		VertexAttrbPointer();
	}

}