#include <core/graphics/RawVertexBuffersPosition.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPosition::RawVertexBuffersPosition(Liar::GeometryVertexType type):
		Liar::IRawVertexBuffers(type),
		m_position(new Liar::SubVector3VertexBuffer())
	{
	}

	RawVertexBuffersPosition::~RawVertexBuffersPosition()
	{
		delete m_position;
		m_position = nullptr;
	}

	Liar::Int RawVertexBuffersPosition::GetSize() const
	{
		return m_position->GetSize();
	}

	// 增加position信息
	void RawVertexBuffersPosition::AddPositionVertexBuffer(void* data)
	{
		m_position->AddVertexBuffer(data);
	}

	// 设置position信息
	void RawVertexBuffersPosition::SetPositionVertexBuffer(Liar::Int index, void* data)
	{
		m_position->SetVertexBuffer(index, data);
	}

	// 设置position长度
	void RawVertexBuffersPosition::SetPositionVertexBufferLen(Liar::Int len)
	{
		m_position->SetVertexBufferLen(len);
	}

	// 获得position信息
	void* RawVertexBuffersPosition::GetPostionVertexBuffer(Liar::Int index) const
	{
		return m_position->GetVertexBuffer(index);
	}

	// 设置 buffer 信息
	void RawVertexBuffersPosition::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) AddPositionVertexBuffer(data);
		else Liar::IRawVertexBuffers::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPosition::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) SetPositionVertexBuffer(index, data);
		else Liar::IRawVertexBuffers::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPosition::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) SetPositionVertexBufferLen(len);
		else Liar::IRawVertexBuffers::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPosition::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) return GetPostionVertexBuffer(index);
		else return Liar::IRawVertexBuffers::GetSubVertexBuffer(attr, index);
	}

	// 获得提交指定顶点属性信息
	void* RawVertexBuffersPosition::GetUploadVertexBuffer(Liar::Int index, Liar::VertexElementAttr attr)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION)
		{
			Liar::IntHeapOperator* key = m_vertexKeys[index];
			Liar::Int posIndex = (*key)[m_vertexIndex++];
			return GetSubVertexBuffer(attr, posIndex);
		}
		else
		{
			return nullptr;
		}
	}

	size_t RawVertexBuffersPosition::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffset = start;
		Liar::Int positionSize = m_position->GetSize();
		void* pos = GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
		gl.BufferSubData(type, positionOffset, positionSize, pos);
		return positionOffset;
	}

	size_t RawVertexBuffersPosition::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positonOffset = 0;
		Liar::Int positonFormat = m_position->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION, positonFormat, GL_FLOAT, GL_FALSE, stride, (void*)positonOffset);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION);
		return positonOffset;
	}
}
