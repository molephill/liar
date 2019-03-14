
#include <core/graphics/RawVertexBuffersPositionNormalTexture.h>
#include <Liar3D.h>

namespace Liar
{
	VertexPositionNormalTextureKey::VertexPositionNormalTextureKey() :
		Liar::VertexPositionKey(),
		m_normalIndex(0), m_texCoordIndex(0)
	{}

	Liar::Boolen VertexPositionNormalTextureKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return
			m_normalIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL) &&
			m_texCoordIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) &&
			m_positonIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION);
	}

	Liar::IVertexKey* VertexPositionNormalTextureKey::Clone() const
	{
		Liar::VertexPositionNormalTextureKey* tmp = new Liar::VertexPositionNormalTextureKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_normalIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_texCoordIndex);
		return tmp;
	}

	void VertexPositionNormalTextureKey::PrintData()
	{
		std::cout << m_positonIndex << "," << m_normalIndex << "," << m_texCoordIndex;
	}

	/*
	* ��������
	*/
	RawVertexBuffersPositionNormalTexture::RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type),
		m_normal(new Liar::SubVector3VertexBuffer()),
		m_texCoord(new Liar::SubVector2VertexBuffer())
	{
	}

	RawVertexBuffersPositionNormalTexture::~RawVertexBuffersPositionNormalTexture()
	{
		delete m_normal;
		m_normal = nullptr;

		delete m_texCoord;
		m_texCoord = nullptr;
	}

	// ����normal��Ϣ
	void RawVertexBuffersPositionNormalTexture::AddNormalVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_normal->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPositionNormalTexture::AddNormalVertexBuffer(const Liar::Vector3& normal)
	{
		AddNormalVertexBuffer(normal.x, normal.y, normal.z);
	}

	// ����normal��Ϣ
	void RawVertexBuffersPositionNormalTexture::SetNormalVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number z)
	{
		SetNormalVertexBuffer(index, new Liar::Vector3(x, y, z));
	}

	void RawVertexBuffersPositionNormalTexture::SetNormalVertexBuffer(size_t index, Liar::Vector3* normal)
	{
		m_normal->SetVertexBuffer(index, normal);
	}

	// ����normal����
	void RawVertexBuffersPositionNormalTexture::SetNormalVertexBufferLen(Liar::Int len)
	{
		m_normal->SetVertexBufferLen(len);
	}

	// ���normal��Ϣ
	void* RawVertexBuffersPositionNormalTexture::GetNormalVertexBuffer(size_t index) const
	{
		return m_normal->GetVertexBuffer(index);
	}

	// ����texcoord��Ϣ
	void RawVertexBuffersPositionNormalTexture::AddTexCoordVertexBuffer(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		m_texCoord->AddVertexBuffer(x, y, z);
	}

	void RawVertexBuffersPositionNormalTexture::AddTexCoordVertexBuffer(const Liar::Vector2& tex)
	{
		AddTexCoordVertexBuffer(tex.x, tex.y);
	}

	// ����texcoord��Ϣ
	void RawVertexBuffersPositionNormalTexture::SetTexCoordVertexBuffer(size_t index, Liar::Number x, Liar::Number y, Liar::Number)
	{
		SetTexCoordVertexBuffer(index, new Liar::Vector2(x, y));
	}

	void RawVertexBuffersPositionNormalTexture::SetTexCoordVertexBuffer(size_t index, Liar::Vector2* tex)
	{
		m_texCoord->SetVertexBuffer(index, tex);
	}

	// ����texcoord����
	void RawVertexBuffersPositionNormalTexture::SetTexCoordVertexBufferLen(Liar::Int len)
	{
		m_texCoord->SetVertexBufferLen(len);
	}

	// ���texcoord��Ϣ
	void* RawVertexBuffersPositionNormalTexture::GetTexCoordVertexBuffer(size_t index) const
	{
		return m_texCoord->GetVertexBuffer(index);
	}

	Liar::Int RawVertexBuffersPositionNormalTexture::GetStride() const
	{
		return  Liar::RawVertexBuffersPosition::GetStride() + m_normal->GetStride() + m_texCoord->GetStride();
	}

	size_t RawVertexBuffersPositionNormalTexture::LoopUploadSubData(Liar::StageContext& gl, GLenum type, Liar::Int i, size_t start)
	{
		size_t positionOffsize = Liar::RawVertexBuffersPosition::LoopUploadSubData(gl, type, i, start);

		Liar::Int positonOffset = m_position->GetStride();
		Liar::Int normalOffset = m_normal->GetStride();
		Liar::Int texCoordOffset = m_texCoord->GetStride();

		size_t normalOffsize = positionOffsize + positonOffset;
		size_t texCoordOffsize = normalOffsize + normalOffset;

		gl.BufferSubData(type, normalOffsize, normalOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL));
		gl.BufferSubData(type, texCoordOffsize, texCoordOffset, GetUploadVertexBuffer(i, Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE));
		return texCoordOffsize;
	}

	size_t RawVertexBuffersPositionNormalTexture::VertexAttrbSubPointer(Liar::StageContext& gl, size_t stride)
	{
		size_t positonOffsize = Liar::RawVertexBuffersPosition::VertexAttrbSubPointer(gl, stride);
		// normal
		size_t normalOffsize = positonOffsize + m_normal->GetStride();
		Liar::Int normalFormat = m_normal->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL, normalFormat, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_NORMAL);
		// texCoord
		size_t texCoordOffsize = normalOffsize + m_normal->GetStride();
		Liar::Int texCoordFromat = m_texCoord->GetFormat();
		gl.VertexAttribPointer(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE, texCoordFromat, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffsize);
		gl.EnableVertexAttribArray(Liar::VertexAttribPointer::ATTRIB_POINTER_TEXTURECOORDINATE);
		return texCoordOffsize;
	}
}