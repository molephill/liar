#include <core/display/Stage.hpp>
#include <Liar3D.h>

namespace Liar
{
    Stage::Stage(Liar::Int w, Liar::Int h):
		m_scenes(nullptr), m_numberChild(0),
		m_cameras(nullptr), m_numberCamera(0),
		m_width(w), m_height(h),
		m_isFirstMove(true), m_lastMouseX(0.0), m_lastMouseY(0.0)
	{
	}

	Stage::~Stage()
	{
		size_t i = 0;
		for (i = 0; i < m_numberChild; ++i)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}

		if (m_scenes) free(m_scenes);
		m_scenes = nullptr;
		m_numberChild = 0;

		for (i = 0; i < m_numberCamera; ++i)
		{
			delete m_cameras[i];
			m_cameras[i] = nullptr;
		}

		if (m_cameras) free(m_cameras);
		m_cameras = nullptr;
		m_numberCamera = 0;
	}

	Liar::Node* Stage::AddChild(Liar::Node* node)
	{
		Liar::Scene* scene = static_cast<Liar::Scene*>(node);
		if (!scene) return node;
		if (m_scenes)
		{
			m_scenes = (Liar::Scene**)realloc(m_scenes, sizeof(Liar::Scene*)*(m_numberChild + 1));
		}
		else
		{
			m_scenes = (Liar::Scene**)malloc(sizeof(Liar::Scene*));
		}
		m_scenes[m_numberChild] = scene;
		++m_numberChild;
		return node;
	}

	Liar::BaseCamera* Stage::AddCamera(Liar::BaseCamera* camera)
	{
		if (!camera) return camera;
		if (m_scenes)
		{
			m_cameras = (Liar::BaseCamera**)realloc(m_cameras, sizeof(Liar::BaseCamera*)*(m_numberChild + 1));
		}
		else
		{
			m_cameras = (Liar::BaseCamera**)malloc(sizeof(Liar::BaseCamera*));
		}
		m_cameras[m_numberCamera] = camera;
		++m_numberCamera;
		return camera;
	}

	bool Stage::OnEnterFrame(Liar::StageContext& gl, Liar::RenderState& state)
	{
		bool rendering = true;

		for (size_t j = 0; j < m_numberCamera; ++j)
		{
			Liar::Liar3D::renderState->camera = m_cameras[j];
			m_cameras[j]->Render(gl, state);

			for (size_t i = 0; i < m_numberChild; ++i)
			{
				rendering = m_scenes[i]->Render(gl, state);
				if (!rendering) break;
			}
		}

		return rendering;
	}

	void Stage::SetSize(Liar::Uint w, Liar::Uint h)
	{
		if (m_width != w || m_height != h)
		{
			m_width = w;
			m_height = h;

			Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
			gl.Viewport(0, 0, w, h);
			gl.Scissor(0, 0, w, h);

			Liar::Liar3D::renderState->clientWidth = w;
			Liar::Liar3D::renderState->clientHeight = h;
		}
	}

	void Stage::MouseEvent(Liar::DNumber x, Liar::DNumber y, Liar::Int state)
	{
		if (state == GLFW_PRESS)
		{
			if (m_isFirstMove)
			{
				m_isFirstMove = false;
			}
			else
			{
				double offsetx = x - m_lastMouseX;
				double offsety = y - m_lastMouseY;
			}
			m_lastMouseX = x;
			m_lastMouseY = y;
		}
		else
		{
			m_isFirstMove = true;
		}
	}

	void Stage::ScrollEvent(Liar::DNumber, Liar::DNumber)
	{

	}
}