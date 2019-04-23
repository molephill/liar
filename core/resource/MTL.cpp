
#include <core/resource/MTL.h>
#include <core/resource/Textrue2D.h>
#include <core/material/StandardMaterial.h>
#include <core/models/geometries/BoxGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	// ≤ƒ÷ π‹¿Ì
	MTL::MTL():
		m_shareResources(nullptr), m_numberShares(0)
	{
	}

	MTL::~MTL()
	{
		Liar::Int i = 0;
		for (i = 0; i < m_numberShares; ++i)
		{
			if (m_shareResources[i])
			{
				delete m_shareResources[i];
				m_shareResources[i] = nullptr;
			}
		}
		if (m_shareResources) free(m_shareResources);
		m_shareResources = nullptr;
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

	Liar::Resource* MTL::CreateResource(const char* path, Liar::ClassType type, void* args)
	{
		Liar::Int nullIndex = -1;
		for (Liar::Int i = 0; i < m_numberShares; ++i)
		{
			if (m_shareResources[i])
			{
				if (m_shareResources[i]->Equals(path)) return m_shareResources[i];
			}
			else
			{
				if (nullIndex == -1) nullIndex = i;
			}
		}

		if (nullIndex == -1)
		{
			nullIndex = m_numberShares++;
			size_t blockSize = sizeof(Liar::Resource*)*m_numberShares;
			if (m_shareResources) m_shareResources = (Liar::Resource**)realloc(m_shareResources, blockSize);
			else m_shareResources = (Liar::Resource**)malloc(blockSize);
		}

		Liar::Resource* tmp = nullptr;

		switch (type)
		{
		case Liar::ClassType::CLASS_NODE_TYPE_TEXTURE:
			tmp = CreateTexture(*(static_cast<Liar::TextureTypeDefine*>(args)));
			break;
		case Liar::ClassType::CLASS_NODE_TYPE_SKELETON:
			tmp = new Liar::Skeleton();
			break;
		case Liar::ClassType::CLASS_NODE_TYPE_GEOMETORY:
			tmp = CreateGeometry(*(static_cast<Liar::GeometryType*>(args)));
			break;
		default:
			break;
		}

		if (tmp)
		{
			tmp->SetURL(path);
			tmp->AddRefrence();
			m_shareResources[nullIndex] = tmp;
		}
		return tmp;
	}

	void MTL::ReduceRefrence(const Liar::Resource* res)
	{
		if (!res) return;
		for (Liar::Int i = 0; i < m_numberShares; ++i)
		{
			if (m_shareResources[i] == res)
			{
				if (m_shareResources[i]->ReduceRefrence() <= 0)
				{
					delete m_shareResources[i];
					m_shareResources[i] = nullptr;
				}
				return;
			}
		}
	}

}