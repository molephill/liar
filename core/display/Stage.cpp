#include <core/display/Stage.hpp>
#include <Liar3D.h>

namespace Liar
{
	Stage::Stage(Liar::Uint w, Liar::Uint h) :
		Liar::Node(),
		m_cameras(nullptr), m_numberCamera(0),
		m_lights(nullptr), m_numberLight(0),
		m_width(w), m_height(h),
		mouseX(0.0f), mouseY(0.0f),
		scrollX(0.0f), scrollY(0.0f)
	{
	}

	Stage::~Stage()
	{
		Liar::Uint i = 0;
		for (i = 0; i < m_numberCamera; ++i)
		{
			delete m_cameras[i];
			m_cameras[i] = nullptr;
		}

		if (m_cameras) free(m_cameras);
		m_cameras = nullptr;
		m_numberCamera = 0;

		for (i = 0; i < m_numberLight; ++i)
		{
			delete m_lights[i];
			m_lights[i] = nullptr;
		}
		if (m_lights) free(m_lights);
		m_lights = nullptr;
		m_numberLight = 0;
	}

	Liar::BaseCamera* Stage::AddCamera(Liar::BaseCamera* camera)
	{
		if (!camera) return camera;
		++m_numberCamera;
		size_t strip = sizeof(Liar::BaseCamera*)*m_numberCamera;
		if (m_cameras) m_cameras = (Liar::BaseCamera**)realloc(m_cameras, strip);
		else m_cameras = (Liar::BaseCamera**)malloc(strip);
		camera->GetTransform3D().SetParent(m_transform3D);
		m_cameras[m_numberCamera - 1] = camera;
		return camera;
	}

	Liar::BaseLight* Stage::AddLight(Liar::BaseLight* light)
	{
		if (!light) return light;
		++m_numberLight;
		size_t strip = sizeof(Liar::BaseLight*)*m_numberLight;
		if (m_lights) m_lights = (Liar::BaseLight**)realloc(m_lights, strip);
		else m_lights = (Liar::BaseLight**)malloc(strip);
		light->GetTransform3D().SetParent(m_transform3D);
		m_lights[m_numberLight - 1] = light;
		return light;
	}

	bool Stage::OnEnterFrame(Liar::RenderState& state)
	{
		bool rendering = true;
		size_t j = 0;

		for (j = 0; j < m_numberLight; ++j)
		{
			m_lights[j]->PrepareRender(state);
		}

		Liar::Int renderCount = 0;
		for (j = 0; j < m_numberCamera; ++j)
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
