
#include <core/render/RenderUnit.h>

namespace Liar
{
	RenderUnit::RenderUnit():
		transform(nullptr), material(nullptr),
		geometry(nullptr), shaderProgram(nullptr)
	{
	}


	RenderUnit::~RenderUnit()
	{
		Clear();
	}

	void RenderUnit::Clear()
	{
		transform = nullptr;
		material = nullptr;
		geometry = nullptr;
		shaderProgram = nullptr;
	}

	void RenderUnit::Render(Liar::RenderState& state)
	{
		shaderProgram->Use();
		shaderProgram->SetMat4("u_MvpMatrix", transform->GetProjectionViewWorldMatrix());
		geometry->Draws();
	}
}