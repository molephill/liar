
#include <core/render/RenderUnit.h>
#include <Liar3D.h>

namespace Liar
{
	RenderUnit::RenderUnit() :
		transform(nullptr),
		geometry(nullptr), material(nullptr)
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
	}

	void RenderUnit::Render(Liar::RenderState& state)
	{
		/*shaderProgram->Use();
		shaderProgram->SetMat4("u_MvpMatrix", transform->GetProjectionViewWorldMatrix());
		geometry->Draws();*/
	}
}