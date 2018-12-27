#pragma once

#include <core/display/Transform3D.h>
#include <core/material/BaseMaterial.h>
#include <core/models/geometries/Geometry.h>
#include <core/resource/shader/ShaderProgram.h>
#include <core/render/RenderState.h>

namespace Liar
{
	class RenderUnit
	{
	public:
		RenderUnit();
		~RenderUnit();

	public:
		Liar::Transform3D* transform;
		Liar::ShaderProgram* shaderProgram;

	private:
		Liar::Geometry** m_geometries;
		Liar::Int m_numberGeometries;
		Liar::BaseMaterial** m_materials;
		Liar::Int m_numberMaterials;

	public:
		void Clear();
		void Render(Liar::RenderState&);

		void AddGeometry(Liar::Geometry*);
		void AddMaterial(Liar::BaseMaterial*);
	};
}