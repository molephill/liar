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
		Liar::BaseMaterial* material;
		Liar::Geometry* geometry;
		Liar::ShaderProgram* shaderProgram;

	public:
		void Clear();
		void Render(Liar::RenderState&);
	};
}