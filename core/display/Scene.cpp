#include <core/display/Scene.h>

namespace Liar
{
	Scene::Scene():
		Liar::TransformNode(),
		m_cameras(nullptr), m_numberCamera(0)
	{
	}


	Scene::~Scene()
	{
	}

	bool Scene::Render()
	{
		return true;
	}
}
