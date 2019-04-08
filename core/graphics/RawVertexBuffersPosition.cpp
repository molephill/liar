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

	// 设置 buffer 信息
	void RawVertexBuffersPosition::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) m_position->AddVertexBuffer(data);
		else Liar::IRawVertexBuffers::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPosition::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) m_position->SetVertexBuffer(index, data);
		else Liar::IRawVertexBuffers::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPosition::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) m_position->SetVertexBufferLen(len);
		else Liar::IRawVertexBuffers::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPosition::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_POSITION) return m_position->GetVertexBuffer(index);
		else return Liar::IRawVertexBuffers::GetSubVertexBuffer(attr, index);
	}

	size_t RawVertexBuffersPosition::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		return m_position->UploadData(gl, type, start, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_POSITION));
	}

	size_t RawVertexBuffersPosition::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		return m_position->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_POSITION, gl, stride);
	}

	void RawVertexBuffersPosition::Print(std::ostream& os) const
	{
		Liar::IRawVertexBuffers::Print(os);
		os << "\npositon:\n";
		m_position->Print(os);
	}
}
