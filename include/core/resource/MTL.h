#pragma once

#include <core/material/BaseMaterial.h>
#include <core/graphics/RawVertexBuffersPositionNormalTextureSkin.h>
#include <core/graphics/RawVertexBuffersPositionColor.h>
#include <core/models/geometries/NetGeometry.h>
#include <core/ani/Skeleton.h>


namespace Liar
{
	class MTL
	{
	public:
		MTL();
		~MTL();

	private:
		Liar::Resource** m_shareResources;
		Liar::Int m_numberShares;

	private:
		Liar::BaseTexture* CreateTexture(Liar::TextureTypeDefine);
		Liar::Geometry* CreateGeometry(Liar::GeometryType);

	public:
		Liar::BaseMaterial* CreateMaterial(Liar::MaterialTypeDefine);
		Liar::IRawVertexBuffers* CreateRawVertexBuffers(Liar::GeometryVertexType);
		void ReduceRefrence(const Liar::Resource*);
		Liar::Resource* CreateResource(const char*, Liar::ClassType, void* = nullptr);
	};

}
