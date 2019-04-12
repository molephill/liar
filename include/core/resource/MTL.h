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

	private:
		Liar::BaseTexture* CreateTexture(Liar::TextureTypeDefine);
		Liar::BaseTexture* GetTexture(const char*);
		Liar::BaseTexture* GetTexture(const Liar::BaseTexture*);

	public:
		Liar::BaseTexture* GetShareTexture(const char*, Liar::TextureTypeDefine);
		Liar::BaseMaterial* CreateMaterial(Liar::MaterialTypeDefine);
		void ReduceTexture(const Liar::BaseTexture*);
		void AddRefTexture(const Liar::BaseTexture*);
		Liar::IRawVertexBuffers* GetRawVertexBuffers(Liar::GeometryVertexType);
		Liar::Geometry* GetGeometry(Liar::GeometryType);
	};

}
