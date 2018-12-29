#pragma once

#include <core/material/BaseMaterial.h>
#include <core/material/MaterialDefine.h>

namespace Liar
{
	class MTL
	{
	public:
		MTL();
		~MTL();

	private:
		Liar::BaseTexture** m_shareTextures;
		Liar::Int m_numberShareTextures;

		Liar::BaseMaterial** m_shareMaterials;
		Liar::Int m_numberShareMaterials;

		Liar::BaseMaterial* GetShareMaterial(const char*, Liar::Int&);
		Liar::BaseTexture* GetShareTexture(const char*, Liar::Int&);

	private:
		Liar::BaseTexture* NewTextrue(Liar::TextureTypeDefine);
		Liar::BaseMaterial* NewMaterial(Liar::MaterialTypeDefine);

	public:
		Liar::BaseMaterial* GetShareMaterial(const char*, Liar::MaterialTypeDefine);
		Liar::BaseTexture* GetShareTexture(const char*, Liar::TextureTypeDefine);
		void DelShareTexture(const char*);
	};

}
