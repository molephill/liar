
#include <core/render/RenderUnit.h>
#include <Liar3D.h>

namespace Liar
{
	RenderUnit::RenderUnit() :
		transform(nullptr),
		geometry(nullptr), 
		material(nullptr),
		skeleton(nullptr)
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
		skeleton = nullptr;
	}

	void RenderUnit::Render(Liar::RenderState& state)
	{
		if (!geometry || !geometry->GetUploaded()) return;
		Liar::ShaderProgram* shaderProgram = Liar::Liar3D::shaderCompile->GetShaderProgram(geometry->GetGeoVertexType());
		shaderProgram->Use();
		shaderProgram->SetMat4("u_MvpMatrix", transform->GetProjectionViewWorldMatrix());
		if (material) material->Draws(*shaderProgram);
		geometry->Draws();
	}
}