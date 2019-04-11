
#include <core/material/MTL.h>
#include <core/resource/Textrue2D.h>
#include <core/material/StandardMaterial.h>
#include <core/models/geometries/BoxGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	// ≤ƒ÷ π‹¿Ì
	MTL::MTL():
		m_shareTextures(nullptr), m_numberShareTextures(0),
		m_shareMaterials(nullptr), m_numberShareMaterials(0)
	{
	}

	MTL::~MTL()
	{
		Liar::Int i = 0;
		for (i = 0; i < m_numberShareMaterials; ++i)
		{
			if (m_shareMaterials[i])
			{
				delete m_shareMaterials[i];
				m_shareMaterials[i] = nullptr;
			}
		}
		if (m_shareMaterials) free(m_shareMaterials);
		m_shareMaterials = nullptr;

		if (m_shareTextures) free(m_shareTextures);
		m_shareTextures = nullptr;

		for (i = 0; i < m_numberNetGeometries; ++i)
		{
			m_netGeometries[i] = nullptr;
		}
		if (m_netGeometries) free(m_netGeometries);
		m_netGeometries = nullptr;
	}

	Liar::BaseTexture* MTL::GetShareTexture(const char* path, Liar::Int& nullIndex)
	{
		nullIndex = -1;
		for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
		{
			Liar::BaseTexture* tmp = m_shareTextures[i];
			if (tmp)
			{
				if (tmp->GetURL() == path)
				{
					tmp->AddRefrence();
					return tmp;
				}
			}
			else
			{
				if (nullIndex < 0) nullIndex = i;
			}
		}

		if (nullIndex < 0)
		{
			nullIndex = m_numberShareTextures++;
			size_t strip = sizeof(Liar::BaseTexture*)*m_numberShareTextures;
			if (m_shareTextures) m_shareTextures = (Liar::BaseTexture**)realloc(m_shareTextures, strip);
			else m_shareTextures = (Liar::BaseTexture**)malloc(strip);
		}

		return nullptr;
	}

	Liar::BaseMaterial* MTL::GetShareMaterial(const char* name, Liar::Int& nullIndex)
	{
		nullIndex = -1;
		for (Liar::Int i = 0; i < m_numberShareMaterials; ++i)
		{
			Liar::BaseMaterial* tmp = m_shareMaterials[i];
			if (tmp)
			{
				if (tmp->GetName() == name)
				{
					tmp->AddRefrence();
					return tmp;
				}
			}
			else
			{
				if (nullIndex < 0) nullIndex = i;
			}
		}

		if (nullIndex < 0)
		{
			nullIndex = m_numberShareMaterials++;
			size_t strip = sizeof(Liar::BaseMaterial*)*m_numberShareMaterials;
			if (m_shareTextures) m_shareMaterials = (Liar::BaseMaterial**)realloc(m_shareMaterials, strip);
			else m_shareMaterials = (Liar::BaseMaterial**)malloc(strip);
		}

		return nullptr;
	}

	Liar::BaseTexture* MTL::NewTextrue(Liar::TextureTypeDefine type)
	{
		switch (type)
		{
		case Liar::TextureTypeDefine::TEXTURE_2D:
			return new Liar::Texture2D();
		default:
			return nullptr;
		}
	}

	Liar::BaseMaterial* MTL::NewMaterial(Liar::MaterialTypeDefine type)
	{
		switch (type)
		{
		case Liar::MaterialTypeDefine::MATERIAL_STANDARD:
			return new Liar::StandardMaterial();
		default:
			return nullptr;
		}
	}

	Liar::BaseTexture* MTL::GetShareTexture(const char* path, Liar::TextureTypeDefine type)
	{
		Liar::Int nullIndex = -1;
		Liar::BaseTexture* tmp = GetShareTexture(path, nullIndex);
		if (!tmp)
		{
			tmp = NewTextrue(type);
			tmp->AddRefrence();
			tmp->SetURL(path);
			m_shareTextures[nullIndex] = tmp;
		}
		return tmp;
	}

	Liar::BaseMaterial* MTL::GetShareMaterial(const char* path, Liar::MaterialTypeDefine type)
	{
		Liar::Int nullIndex = -1;
		Liar::BaseMaterial* tmp = GetShareMaterial(path, nullIndex);
		if (!tmp)
		{
			tmp = NewMaterial(type);
			tmp->AddRefrence();
			tmp->SetName(path);
			m_shareMaterials[nullIndex] = tmp;
		}
		return tmp;
	}

	void MTL::DelShareTexture(const char* path)
	{
		for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
		{
			Liar::BaseTexture* tmp = m_shareTextures[i];
			if (tmp && tmp->GetURL() == path)
			{
				m_shareTextures[i] = nullptr;
				return;
			}
		}
	}

	void MTL::DelShareMaterial(const char* name)
	{
		for (Liar::Int i = 0; i < m_numberShareMaterials; ++i)
		{
			Liar::BaseMaterial* tmp = m_shareMaterials[i];
			if (tmp && tmp->GetName() == name)
			{
				m_shareMaterials[i] = nullptr;
				return;
			}
		}
	}

	void MTL::DelShareTexture(const Liar::BaseTexture* tex)
	{
		if (tex)
		{
			for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
			{
				Liar::BaseTexture* tmp = m_shareTextures[i];
				if (tmp == tex)
				{
					m_shareTextures[i] = nullptr;
					return;
				}
			}
		}
	}

	void MTL::DelShareMaterial(const Liar::BaseMaterial* mat)
	{
		if (mat)
		{
			for (Liar::Int i = 0; i < m_numberShareMaterials; ++i)
			{
				Liar::BaseMaterial* tmp = m_shareMaterials[i];
				if (tmp == mat)
				{
					m_shareMaterials[i] = nullptr;
					return;
				}
			}
		}
	}

	// ================ get buffers ========================= //
	Liar::IRawVertexBuffers* MTL::GetRawVertexBuffers(Liar::GeometryVertexType attr)
	{
		switch (attr)
		{
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION:
			return new Liar::RawVertexBuffersPosition(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
			return new Liar::RawVertexBuffersPositionColor(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
			return new Liar::RawVertexBuffersPositionNormal(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			return new Liar::RawVertexBuffersPositionNormalTexture(attr);
		case Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE_SKIN:
			return new Liar::RawVertexBuffersPositionNormalTextureSkin(attr);
		default:
			return nullptr;
		}
	}

	// =============================== get geometry ===========================
	Liar::Geometry* MTL::GetGeometry(Liar::GeometryType type)
	{
		switch (type)
		{
		case Liar::GeometryType::GEOMETRY_TYPE_BOX:
		{
			Liar::BoxGeometry* box = new Liar::BoxGeometry();
			box->AddRefrence();
			box->SetGeometryVertexType(Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE);
			return box;
		}
		default:
			return nullptr;
		}
	}

	Liar::Geometry* MTL::GetGeometry(const char* url)
	{
		Liar::NetGeometry* tmp = nullptr;
		for (Liar::Int i = 0; i < m_numberNetGeometries; ++i)
		{
			tmp = m_netGeometries[i];
			if ((*tmp) == url)
			{
				tmp->AddRefrence();
				return tmp;
			}
		}

		++m_numberNetGeometries;
		size_t len = sizeof(Liar::NetGeometry*)*m_numberNetGeometries;
		if (m_netGeometries) m_netGeometries = (Liar::NetGeometry**)realloc(m_netGeometries, len);
		else m_netGeometries = (Liar::NetGeometry**)malloc(len);

		tmp = new Liar::NetGeometry();
		tmp->AddRefrence();
		tmp->SetURL(url);
		m_netGeometries[m_numberNetGeometries - 1] = tmp;
		return tmp;
	}

}