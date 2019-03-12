#include <core/graphics/RawVertexBuffersPostionTexture.h>

namespace Liar
{
	VertexPositionTextureKey::VertexPositionTextureKey() :
		Liar::VertexPositionKey(),
		m_texIndex(0)
	{}

	void VertexPositionTextureKey::SetVertexIndex(Liar::VertexElementAttr attr, Liar::Uint index)
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			m_texIndex = index;
			break;
		default:
			Liar::VertexPositionKey::SetVertexIndex(attr, index);
			break;
		}
	}

	Liar::Uint VertexPositionTextureKey::GetVertexIndex(Liar::VertexElementAttr attr) const
	{
		switch (attr)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			return m_texIndex;
		default:
			return Liar::VertexPositionKey::GetVertexIndex(attr);
		}
	}

	Liar::Boolen VertexPositionTextureKey::operator==(const Liar::IVertexKey& rhs) const
	{
		return	m_texIndex == rhs.GetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE) && Liar::VertexPositionKey::operator==(rhs);
	}

	Liar::IVertexKey* VertexPositionTextureKey::Clone() const
	{
		Liar::VertexPositionTextureKey* tmp = new Liar::VertexPositionTextureKey();
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_positonIndex);
		tmp->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_texIndex);
		return tmp;
	}

	void VertexPositionTextureKey::PrintData()
	{
		Liar::VertexPositionKey::PrintData();
		std::cout << "," << m_texIndex;
	}

	/*
	* 具体数据
	*/
	RawVertexBuffersPostionTexture::RawVertexBuffersPostionTexture(Liar::GeometryVertexType type):
		Liar::RawVertexBuffersPosition(type)
	{
	}

	RawVertexBuffersPostionTexture::~RawVertexBuffersPostionTexture()
	{
	}
}
