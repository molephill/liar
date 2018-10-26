#include "Stage.hpp"

namespace Liar
{
    Stage::Stage(Liar::uint w, Liar::uint h):
		m_width(w), m_height(h),
		m_isActive(true),
		m_red(0.2f), m_green(0.3f), m_blue(0.3f)
	{
		m_openglMainWindow = new OpenGLWindow("LiarMainOpenGL", this);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glEnable(GL_DEPTH_TEST);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		SetSize(w, h);
	}

	bool Stage::Run()
	{
		glClearColor(m_red, m_green, m_blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return true;
	}

	void Stage::SetSize(Liar::uint w, Liar::uint h)
	{
		if (m_width != w || m_height != h)
		{
			m_width = w;
			m_height = h;
		}

		glViewport(0, 0, w, h);
		glScissor(0, 0, w, h);
	}

	Stage::~Stage()
	{
        delete m_openglMainWindow;
	}
}
