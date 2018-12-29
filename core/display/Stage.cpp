#include <core/display/Stage.hpp>
#include <Liar3D.h>

namespace Liar
{
	Stage::Stage(Liar::Int w, Liar::Int h) :
		Liar::Node(),
		m_cameras(nullptr), m_numberCamera(0),
		m_width(w), m_height(h),
		mouseX(0.0f), mouseY(0.0f),
		scrollX(0.0f), scrollY(0.0f)
	{
	}

	Stage::~Stage()
	{
		for (size_t i = 0; i < m_numberCamera; ++i)
		{
			delete m_cameras[i];
			m_cameras[i] = nullptr;
		}

		if (m_cameras) free(m_cameras);
		m_cameras = nullptr;
		m_numberCamera = 0;
	}

	Liar::BaseCamera* Stage::AddCamera(Liar::BaseCamera* camera)
	{
		if (!camera) return camera;
		if (m_cameras)
		{
			m_cameras = (Liar::BaseCamera**)realloc(m_cameras, sizeof(Liar::BaseCamera*)*(m_numberChild + 1));
		}
		else
		{
			m_cameras = (Liar::BaseCamera**)malloc(sizeof(Liar::BaseCamera*));
		}
		camera->GetTransform3D().SetParent(m_transform3D);
		m_cameras[m_numberCamera] = camera;
		++m_numberCamera;
		return camera;
	}


	bool Stage::OnEnterFrame(Liar::RenderState& state)
	{
		bool rendering = true;
		Liar::Int renderCount = 0;
		for (size_t j = 0; j < m_numberCamera; ++j)
		{
			Liar::Liar3D::renderState->camera = m_cameras[j];
			m_cameras[j]->Render(state);
			m_transform3D->CalclateTransformation(&(m_cameras[j]->GetProjectionViewMatrix()));
			renderCount += CollectRenderUint(state);
		}
		return rendering;
	}

	Liar::Int Stage::CollectRenderUint(Liar::RenderState& state)
	{
		return CollectChildrenRenderUint(state);
	}

	void Stage::SetSize(Liar::Uint w, Liar::Uint h)
	{
		if (m_width != w || m_height != h)
		{
			m_width = w;
			m_height = h;

			Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
			gl.Viewport(0, 0, w, h);
			gl.Scissor(0, 0, w, h);

			Liar::Liar3D::renderState->clientWidth = w;
			Liar::Liar3D::renderState->clientHeight = h;
		}
	}

}
