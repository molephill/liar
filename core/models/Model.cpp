
#include <core/models/Model.h>
#include <Liar3D.h>

namespace Liar
{
	Model::Model() :
		Liar::Node(),
		m_url("")
	{
	}

	Model::~Model()
	{
	}

	void Model::RemoveAllMeshs()
	{
		if (m_childs)
		{
			for (Liar::Int i = m_numberChild; i >= 0; --i)
			{
				Liar::Node* node = m_childs[i];
				Liar::Mesh* mesh = static_cast<Liar::Mesh*>(node);
				if (mesh) mesh->RemoveSelf();
			}
		}
	}

	Liar::Int Model::CollectRenderUint(Liar::RenderState& state, bool buildShader)
	{
		return CollectChildrenRenderUint(state, buildShader);
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

			// º”‘ÿÀ˘”– mesh
			Liar::Int meshSize = 0;
			std::string tmpName = name;
			fread(&meshSize, strip, 1, pFile);

			// materials
			Liar::Int materialSize = 0;
			fread(&materialSize, strip, 1, pFile);

			for (Liar::Int i = 0; i < materialSize; ++i)
			{
				// texture
				Liar::Int texSize = 0;
				fread(&texSize, strip, 1, pFile);

				for (Liar::Int j = 0; j < texSize; ++j)
				{
					Liar::Int mapSlot = 0;
					fread(&mapSlot, strip, 1, pFile);
					std::string tmpBitmapPath = Liar::MathUtils3D::ReadString(pFile);
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