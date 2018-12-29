#pragma once

#include <core/models/Mesh.h>

namespace Liar
{
	class Model:public Liar::Node
	{
	public:
		Model();
		virtual ~Model();

	protected:
		std::string m_url;
		Liar::BaseMaterial** m_sharedMaterials;
		Liar::Int m_numberSharedMaterials;

	protected:
		void RemoveAllMeshs();

		void SetNumberSharedMaterial(Liar::Int);
		void SetSharedMaterial(Liar::BaseMaterial*, Liar::Int);

	public:
		void SetURL(const char*);
		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
	};
}