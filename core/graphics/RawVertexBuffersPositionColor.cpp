#include <core/graphics/RawVertexBuffersPositionColor.h>
#include <Liar3D.h>

namespace Liar
{
	/*
	* 具体数据
	*/
	RawVertexBuffersPositionColor::RawVertexBuffersPositionColor(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_color(new Liar::SubVector3VertexBuffer())
	{
	}


	RawVertexBuffersPositionColor::~RawVertexBuffersPositionColor()
	{
		delete m_color;
		m_color = nullptr;
	}

	Liar::Int RawVertexBuffersPositionColor::GetSize() const
	{
		return  Liar::RawVertexBuffersPosition::GetSize() + m_color->GetSize();
	}

	// 设置 buffer 信息
	void RawVertexBuffersPositionColor::AddSubVertexBuffer(Liar::VertexElementAttr attr, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->AddVertexBuffer(data);
		else Liar::RawVertexBuffersPosition::AddSubVertexBuffer(attr, data);
	}

	void RawVertexBuffersPositionColor::SetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index, void* data)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->SetVertexBuffer(index, data);
		else Liar::RawVertexBuffersPosition::SetSubVertexBuffer(attr, index, data);
	}

	void RawVertexBuffersPositionColor::SetSubVertexBufferLen(Liar::VertexElementAttr attr, Liar::Int len)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) m_color->SetVertexBufferLen(len);
		else Liar::RawVertexBuffersPosition::SetSubVertexBufferLen(attr, len);
	}

	// 取得 buffer
	void* RawVertexBuffersPositionColor::GetSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Int index)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_COLOR) return m_color->GetVertexBuffer(index);
		else return Liar::RawVertexBuffersPosition::GetSubVertexBuffer(attr, index);
	}

	size_t RawVertexBuffersPositionColor::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t offset = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);
		return m_color->UploadData(gl, type, offset,
			GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_COLOR));
	}

	size_t RawVertexBuffersPositionColor::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t offset = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		return m_color->AttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, gl, stride, offset);
	}

	void RawVertexBuffersPositionColor::Print(std::ostream& os) const
	{
		Liar::RawVertexBuffersPosition::Print(os);
		os << "\ncolor:\n";
		m_color->Print(os);
	}
}