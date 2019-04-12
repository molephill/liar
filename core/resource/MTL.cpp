
#include <core/resource/MTL.h>
#include <core/resource/Textrue2D.h>
#include <core/material/StandardMaterial.h>
#include <core/models/geometries/BoxGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	// ���ʹ���
	MTL::MTL():
		m_shareTextures(nullptr), m_numberShareTextures(0)
	{
	}

	MTL::~MTL()
	{
		Liar::Int i = 0;
		for (i = 0; i < m_numberShareTextures; ++i)
		{
			if (m_shareTextures[i])
			{
				delete m_shareTextures[i];
				m_shareTextures[i] = nullptr;
			}
		}
		if (m_shareTextures) free(m_shareTextures);
		m_shareTextures = nullptr;
	}

	Liar::BaseTexture* MTL::GetTexture(const char* path)
	{
		for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
		{
			Liar::BaseTexture* tmp = m_shareTextures[i];
			if (tmp && tmp->Equals(path)) return tmp;
		}
		return nullptr;
	}

	Liar::BaseTexture* MTL::GetTexture(const Liar::BaseTexture* tex)
	{
		for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
		{
			Liar::BaseTexture* tmp = m_shareTextures[i];
			if (tmp && tmp == tex) return tmp;
		}
		return nullptr;
	}

	Liar::BaseTexture* MTL::GetShareTexture(const char* path, Liar::TextureTypeDefine type)
	{
		Liar::Int nullIndex = -1;
		Liar::BaseTexture* tmp = nullptr;
		for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
		{
			Liar::BaseTexture* ttmp = m_shareTextures[i];
			if (tmp)
			{
				if (tmp->Equals(path))
				{
					tmp = ttmp;
					break;
				}
			}
			else
			{
				if (nullIndex == -1) nullIndex = i;
			}
		}

		if (!tmp)
		{
			if (nullIndex == -1)
			{
				m_numberShareTextures++;
				size_t strip = sizeof(Liar::BaseTexture*)*m_numberShareTextures;
				if (m_shareTextures) m_shareTextures = (Liar::BaseTexture**)realloc(m_shareTextures, strip);
				else m_shareTextures = (Liar::BaseTexture**)malloc(strip);
				nullIndex = m_numberShareTextures - 1;
			}

			tmp = CreateTexture(type);
			tmp->AddRefrence();
			tmp->SetURL(path);
			m_shareTextures[nullIndex] = tmp;
		}
		return tmp;
	}

	void MTL::ReduceTexture(const Liar::BaseTexture* tex)
	{
		if (tex)
		{
			for (Liar::Int i = 0; i < m_numberShareTextures; ++i)
			{
				Liar::BaseTexture* tmp = m_shareTextures[i];
				if (tmp == tex)
				{
					if (tmp->ReduceRefrence() <= 0)
					{
						delete m_shareTextures[i];
						m_shareTextures[i] = nullptr;
					}
					return;
				}
			}
		}
	}

	void MTL::AddRefTexture(const Liar::BaseTexture* tex)
	{
		Liar::BaseTexture* tmp = GetTexture(tex);
		if (tmp) tmp->AddRefrence();
	}

	Liar::BaseTexture* MTL::CreateTexture(Liar::TextureTypeDefine type)
	{
		switch (type)
		{
		case Liar::TextureTypeDefine::TEXTURE_2D:
			return new Liar::Texture2D();
		default:
			return nullptr;
		}
	}

	Liar::BaseMaterial* MTL::CreateMaterial(Liar::MaterialTypeDefine type)
	{
		switch (type)
		{
		case Liar::MaterialTypeDefine::MATERIAL_STANDARD:
			return new Liar::StandardMaterial();
		default:
			return nullptr;
		}
	}

	// ================ get buffers ========================= //
	Liar::IRawVertexBuffers* MTL::CreateRawVertexBuffers(Liar::GeometryVertexType attr)
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
	Liar::Geometry* MTL::CreateGeometry(Liar::GeometryType type)
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
		case Liar::GeometryType::GEOMETRY_NET:
		{
			Liar::NetGeometry* net = new Liar::NetGeometry();
			net->AddRefrence();
			return net;
		}
		default:
			return nullptr;
		}
	}

}