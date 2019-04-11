#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据处理
	*/
	IRawVertexBuffers::IRawVertexBuffers(Liar::GeometryVertexType vertextype) :
		m_geomtryVertexType(vertextype),
		m_indices(nullptr), m_numberIndices(0),
		m_vertexKeys(nullptr), m_numberVertexKeys(0),
		m_mtlIndex(-1), m_vertexIndex(0), 
		m_loopStep(0)
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
		return GetSize() * m_numberVertexKeys;
	}

	void IRawVertexBuffers::AddRawKeyVertexBuffer(Liar::IntHeapOperator* data)
	{
		if (!data) return;
		SetRawKeyVertexBufferLen(m_numberVertexKeys + 1);
		m_vertexKeys[m_numberVertexKeys - 1] = data;
	}

	void IRawVertexBuffers::SetRawKeyVertexBuffer(Liar::Int index, Liar::IntHeapOperator* data)
	{
		if (index >= m_numberVertexKeys) return;
		if (m_vertexKeys[index] != data && m_vertexKeys[index]) delete m_vertexKeys[index];
		m_vertexKeys[index] = data;
	}

	// 设置raw_key长度
	void IRawVertexBuffers::SetRawKeyVertexBufferLen(Liar::Int len)
	{
		if (m_numberVertexKeys == len) return;
		Liar::Int pre = m_numberVertexKeys;
		m_numberVertexKeys = len;
		size_t blockSize = sizeof(Liar::IntHeapOperator*)*m_numberVertexKeys;
		if (m_vertexKeys) m_vertexKeys = (Liar::IntHeapOperator**)realloc(m_vertexKeys, blockSize);
		else m_vertexKeys = (Liar::IntHeapOperator**)malloc(blockSize);
		for (Liar::Int i = pre; i < m_numberVertexKeys; ++i) m_vertexKeys[i] = nullptr;
	}

	// 设置raw_indexraw_index
	void IRawVertexBuffers::SetRawIndexLen(Liar::Int len)
	{
		m_numberIndices = len;
		size_t blockSize = sizeof(Liar::Uint)*m_numberIndices;
		if (m_indices) m_indices = (Liar::Uint*)realloc(m_indices, blockSize);
		else m_indices = (Liar::Uint*)malloc(blockSize);
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
	void IRawVertexBuffers::SetRawIndex(Liar::Int index, Liar::Uint x)
	{
		m_indices[index] = x;
	}

	// 获得raw_index信息
	void* IRawVertexBuffers::GetRawIndex(Liar::Int index) const
	{
		return &(m_indices[index]);
	}

	// 获得提交指定顶点属性信息
	void* IRawVertexBuffers::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		Liar::IntHeapOperator* key = m_vertexKeys[index];
		Liar::Int vertxIndex = (*key)[m_vertexIndex++];
		return GetSubVertexBuffer(attr, vertxIndex);
	}

	void IRawVertexBuffers::AddSubVertexBuffer(Liar::VertexElementAttr type, void* data)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
			AddRawKeyVertexBuffer(static_cast<Liar::IntHeapOperator*>(data));
			break;
		default:
			break;
		}
	}

	void IRawVertexBuffers::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		switch (attr)
		{
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

	void IRawVertexBuffers::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
			SetRawKeyVertexBuffer(index, static_cast<Liar::IntHeapOperator*>(data));
			break;
		default:
			break;
		}
	}

	void* IRawVertexBuffers::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY:
			return GetRawKeyVertexBuffer(index);
		case Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES:
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
		Liar::Liar3D::tickRender->AddTickRender(this, &type);
	}

	Liar::Boolen IRawVertexBuffers::GetUploaded() const
	{
		return (m_numberVertexKeys > 0 && m_loopStep >= m_numberVertexKeys);
	}

	bool IRawVertexBuffers::TickRender(void* args, Liar::Int delSec)
	{
		Liar::RenderState& state = *(Liar::Liar3D::renderState);
		Liar::StageContext& gl = *(state.stageContext);

		// 提交具体数据
		Liar::Int stride = GetSize();
		//GLenum type = GL_ARRAY_BUFFER;
		//if (args) type = *(GLenum*)args;
		while(m_loopStep < m_numberVertexKeys)
		{
			m_vertexIndex = 0;
			size_t start = m_loopStep * stride;
			LoopUploadSubData(gl, GL_ARRAY_BUFFER, m_loopStep, start);
			++m_loopStep;
			if (Liar::Liar3D::GetTimer() - state.lastCurrentTime >= delSec) return false;
		}
		// 绑定
		VertexAttrbSubPointer(gl, stride);
		return true;
	}

	void IRawVertexBuffers::Print(std::ostream& os) const
	{
		Liar::Int i = 0;
		os << "indices:\n";
		for (i = 0; i < m_numberIndices; ++i) os << m_indices[i] << ",";
		os << "\nkeys:\n";
		for (i = 0; i < m_numberVertexKeys; ++i) os << *(m_vertexKeys[i]) << ",";
	}
}