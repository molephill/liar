
#include <core/render/RenderUnit.h>

namespace Liar
{
	RenderUnit::RenderUnit() :
		transform(nullptr),
		geometry(nullptr), material(nullptr),
		shaderCompile(nullptr)
	{
	}

	RenderUnit::~RenderUnit()
	{
		Clear();
	}

	void RenderUnit::Clear()
	{
		transform = nullptr;
		geometry = nullptr;
		material = nullptr;
		shaderCompile = nullptr;
	}

	void RenderUnit::Render(Liar::RenderState& state, const Liar::Geometry* preGeometry, const Liar::BaseMaterial* preMaterial, const Liar::ShaderCompile* preShaderCompile)
	{
		/*shaderProgram->Use();
		shaderProgram->SetMat4("u_MvpMatrix", transform->GetProjectionViewWorldMatrix());
		geometry->Draws();*/

		preGeometry = geometry;
		preMaterial = material;
		preShaderCompile = shaderCompile;
	}
}