#pragma once

#include <core/material/BaseMaterial.h>
#include <core/material/MaterialDefine.h>
#include <core/graphics/RawVertexBuffersPositionNormalTextureSkin.h>
#include <core/graphics/RawVertexBuffersPositionColor.h>
#include <core/models/geometries/Geometry.h>
#include <core/models/geometries/NetGeometry.h>


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

		Liar::NetGeometry** m_netGeometries;
		Liar::Int m_numberNetGeometries;

	private:
		Liar::BaseTexture* NewTextrue(Liar::TextureTypeDefine);
		Liar::BaseMaterial* NewMaterial(Liar::MaterialTypeDefine);

	public:
		Liar::BaseMaterial* GetShareMaterial(const char*, Liar::MaterialTypeDefine);
		Liar::BaseTexture* GetShareTexture(const char*, Liar::TextureTypeDefine);
		void DelShareTexture(const char*);
		void DelShareMaterial(const char*);
		void DelShareTexture(const Liar::BaseTexture*);
		void DelShareMaterial(const Liar::BaseMaterial*);
		Liar::IRawVertexBuffers* GetRawVertexBuffers(Liar::GeometryVertexType);
		Liar::Geometry* GetGeometry(Liar::GeometryType);
		Liar::Geometry* GetGeometry(const char*);
	};

}
