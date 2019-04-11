#pragma once

#include <core/models/Mesh.h>
#include <core/ani/Skeleton.h>

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
		Liar::Skeleton* m_skeleton;

	protected:
		void RemoveAllMeshs();

		void SetNumberSharedMaterial(Liar::Int);
		void SetSharedMaterial(Liar::BaseMaterial*, Liar::Int);

	public:
		void SetURL(const char*, const char* = nullptr);
		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
		virtual Liar::ClassType GetNodeType() const { return Liar::ClassType::CLASS_NODE_TYPE_MODEL; };
	};
}