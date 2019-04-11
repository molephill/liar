
#include <core/models/Model.h>
#include <core/material/StandardMaterial.h>
#include <core/resource/Textrue2D.h>
#include <Liar3D.h>

namespace Liar
{
	Model::Model() :
		Liar::Node(),
		m_url(""),
		m_sharedMaterials(nullptr), m_numberSharedMaterials(0),
		m_skeleton(nullptr)
	{
		//m_preCompileShader = Liar::Liar3D::shaderCompile->GetPreCompileShader("TEST");
	}

	Model::~Model()
	{
		for (Liar::Int i = 0; i < m_numberSharedMaterials; ++i)
		{
			m_sharedMaterials[i]->ReduceRefrence();
			m_sharedMaterials[i] = nullptr;
		}
		if (m_sharedMaterials) free(m_sharedMaterials);
		m_sharedMaterials = nullptr;

		if (m_skeleton)
		{
			m_skeleton->ReduceRefrence();
			m_skeleton = nullptr;
		}
	}

	void Model::RemoveAllMeshs()
	{
		if (m_childs)
		{
			for (Liar::Uint i = 0; i < m_numberChild; ++i)
			{
				Liar::Node* node = m_childs[i];
				if (node->GetNodeType() == Liar::ClassType::CLASS_NODE_TYPE_MESH) node->RemoveSelf();
			}
		}
	}

	void Model::SetNumberSharedMaterial(Liar::Int len)
	{
		if (len > m_numberSharedMaterials)
		{
			size_t strip = sizeof(Liar::BaseMaterial*)*len;
			if (m_sharedMaterials) m_sharedMaterials = (Liar::BaseMaterial**)realloc(m_sharedMaterials, strip);
			else m_sharedMaterials = (Liar::BaseMaterial**)malloc(strip);
		}
		else
		{
			for (Liar::Int i = len; i < m_numberSharedMaterials; ++i)
			{
				if (m_sharedMaterials[i])
				{
					m_sharedMaterials[i]->ReduceRefrence();
					free(m_sharedMaterials[i]);
					m_sharedMaterials[i] = nullptr;
				}
			}
		}
		m_numberSharedMaterials = len;
	}

	void Model::SetSharedMaterial(Liar::BaseMaterial* mat, Liar::Int index)
	{
		if (mat) m_sharedMaterials[index] = mat;
	}

	Liar::Int Model::CollectRenderUint(Liar::RenderState& state)
	{
		m_transform3D->CalclateTransformation(&(state.camera->GetProjectionViewMatrix()));
		return CollectChildrenRenderUint(state);
	}

	void Model::SetURL(const char* name, const char* ske)
	{
		if (strcmp(m_url.c_str(), name) != 0)
		{
			m_url = name;
			SetName(name);
			RemoveAllMeshs();

			std::string realPath = Liar::Liar3D::urlFormat->FormatSourceURL(m_url.c_str()) + ".MTL";//Liar::mtlSzChar;

			std::string tmpName = name;
			std::string folderName = Liar::StringParse::GetHead(m_url, "\\");
			folderName += "\\";

			Liar::ByteArray* byte = Liar::Liar3D::LiarLoad(realPath.c_str());
			Liar::Int meshSize = byte->ReadInt();
			Liar::Int materialSize = byte->ReadInt();
			SetNumberSharedMaterial(materialSize);
			for (Liar::Int i = 0; i < materialSize; ++i)
			{
				Liar::BaseMaterial* mat = Liar::Liar3D::mtl->GetShareMaterial(name, Liar::MaterialTypeDefine::MATERIAL_STANDARD);
				SetSharedMaterial(mat, i);
				// texture
				Liar::Int texSize = byte->ReadInt();

				for (Liar::Int j = 0; j < texSize; ++j)
				{
					Liar::Int mapSlot = byte->ReadInt();
					std::string tmpBitmapPath = byte->ReadString();
					tmpBitmapPath = folderName + tmpBitmapPath;

					Liar::BaseTexture* tex = Liar::Liar3D::mtl->GetShareTexture(tmpBitmapPath.c_str(), Liar::TextureTypeDefine::TEXTURE_2D);
					mat->SetAmbientTexture(tex);
				}
			}

			for (Liar::Int i = 0; i < meshSize; ++i)
			{
				Liar::Mesh* subMesh = new Liar::Mesh(Liar::GeometryType::GEOMETRY_NONE);
				tmpName = name + std::to_string(i) + ".MESH";//Liar::meshSzChar;
				subMesh->SetGeometryType(tmpName.c_str(), m_sharedMaterials);
				AddChild(subMesh);
			}

			delete byte;
		}

		// skeleteon
		if (!ske || (m_skeleton && m_skeleton->Equals(ske))) return;
		
	}
}