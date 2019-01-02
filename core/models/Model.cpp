
#include <core/models/Model.h>
#include <core/material/StandardMaterial.h>
#include <core/resource/Textrue2D.h>
#include <Liar3D.h>

namespace Liar
{
	Model::Model() :
		Liar::Node(),
		m_url(""),
		m_sharedMaterials(nullptr), m_numberSharedMaterials(0)
	{
		m_preCompileShader = Liar::Liar3D::shaderCompile->GetPreCompileShader("TEST");
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
	}

	void Model::RemoveAllMeshs()
	{
		if (m_childs)
		{
			for (Liar::Uint i = 0; i < m_numberChild; ++i)
			{
				Liar::Mesh* mesh = static_cast<Liar::Mesh*>(m_childs[i]);
				if (mesh) mesh->RemoveSelf();
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
					delete m_sharedMaterials[i];
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
		return CollectChildrenRenderUint(state);
	}

	void Model::SetURL(const char* name)
	{
		if (strcmp(m_url.c_str(), name) != 0)
		{
			m_url = name;
			SetName(name);
			RemoveAllMeshs();

			std::string realPath = Liar::Liar3D::urlFormat->FormatSourceURL(m_url.c_str()) + ".MTL";
			FILE* pFile;
#ifndef __APPLE__
			fopen_s(&pFile, realPath.c_str(), "rb+");
#else
			pFile = fopen(path, "rb+");
#endif

			// strip
			size_t strip = sizeof(Liar::Int);

			// �������� mesh
			Liar::Int meshSize = 0;
			std::string tmpName = name;
			fread(&meshSize, strip, 1, pFile);

			// materials
			Liar::Int materialSize = 0;
			fread(&materialSize, strip, 1, pFile);

			SetNumberSharedMaterial(materialSize);

			for (Liar::Int i = 0; i < materialSize; ++i)
			{
				Liar::BaseMaterial* mat = Liar::Liar3D::mtl->GetShareMaterial(name, Liar::MaterialTypeDefine::MATERIAL_STANDARD);
				SetSharedMaterial(mat, i);
				// texture
				Liar::Int texSize = 0;
				fread(&texSize, strip, 1, pFile);

				for (Liar::Int j = 0; j < texSize; ++j)
				{
					Liar::Int mapSlot = 0;
					fread(&mapSlot, strip, 1, pFile);
					std::string tmpBitmapPath = Liar::MathUtils3D::ReadString(pFile);
					
					Liar::BaseTexture* tex = Liar::Liar3D::mtl->GetShareTexture(tmpBitmapPath.c_str(), Liar::TextureTypeDefine::TEXTURE_2D);
					mat->SetAmbientTexture(tex);
				}
			}

			fclose(pFile);

			for (Liar::Int i = 0; i < meshSize; ++i)
			{
				Liar::Mesh* subMesh = new Liar::Mesh(Liar::GeometryType::GEOMETRY_NONE);
				tmpName = name;
				tmpName = name + std::to_string(i) + ".MESH";
				subMesh->SetGeometryType(tmpName.c_str());
				AddChild(subMesh);
			}
		}
	}
}