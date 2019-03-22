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

	Liar::Int RawVertexBuffersPosition::GetStride() const
	{
		return m_position->GetStride();
	}

	// 增加position信息
	void RawVertexBuffersPosition::AddPositionVertexBuffer(Liar::IHeapOperator* data)
	{
		m_position->AddVertexBuffer(data);
	}

	// 设置position信息
	void RawVertexBuffersPosition::SetPositionVertexBuffer(Liar::Int index, Liar::IHeapOperator* data)
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
	void RawVertexBuffersPosition::AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::IHeapOperator* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) AddPositionVertexBuffer(data);
		else Liar::IRawVertexBuffers::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPosition::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, Liar::IHeapOperator* data)
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
		size_t positionOffsize = start;
		Liar::Int offset = m_position->GetStride();
		gl.BufferSubData(type, positionOffsize, offset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION));
		return positionOffsize;
	}

	size_t RawVertexBuffersPosition::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		// position
		size_t positonOffsie = 0;
		Liar::Int positonFormat = m_position->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION, positonFormat, GL_FLOAT, GL_FALSE, stride, (void*)positonOffsie);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION);
		return positonOffsie;
	}

	void RawVertexBuffersPosition::VertexAttrbPointer()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t stride = GetStride();
		VertexAttrbSubPointer(gl, stride);
	}
}
