//
//  OpenGLWindow.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "OpenGLWindow.hpp"
#include <Stage.hpp>

namespace Liar
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	OpenGLWindow::OpenGLWindow(std::string title, Liar::Stage* stage) :
		m_renderStage(stage),
		m_isFirstMove(true),
		m_lastMouseX(0.0), m_lastMouseY(0.0)
    {
		glfwInit();

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(stage->GetWidth(), stage->GetHeight(), title.c_str(), NULL, NULL);

		if (!window) {
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		OpenGLWindow::runWindow = this;

		Run(window, true);
    }

	OpenGLWindow::~OpenGLWindow()
	{
	}

	void OpenGLWindow::Run(GLFWwindow* window, bool run)
	{
		if (!run) return;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();

			run = m_renderStage->Run();
		}
		else
		{
			run = false;
		}
		Run(window, run);
	}

	void OpenGLWindow::SetSize(GLFWwindow* window, Liar::uint w, Liar::uint h)
	{
		m_renderStage->SetSize(w, h);
	}

	bool OpenGLWindow::MouseEvent(GLFWwindow* window, double x, double y)
	{
		int sx = 0, sy = 0;
		int w = 0, h = 0;

		glfwGetWindowPos(window, &sx, &sy);
		glfwGetWindowSize(window, &w, &h);

		int ex = sx + w;
		int ey = sy + h;

		bool inWindow = x >= sx && x <= ex && y >= sy && y <= ey;

		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (inWindow)
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
		return true;
	}

	Liar::OpenGLWindow* Liar::OpenGLWindow::runWindow = nullptr;


	void OpenGLWindow::ScrollEvent(GLFWwindow* window, double offsetx, double offsety)
	{
       // Camera* mainCamera = m_renderMgr->GetCamera();
       // mainCamera->AddFov(-offsety);
	}

	// 修改屏幕大小时
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		Liar::OpenGLWindow::runWindow->SetSize(window, width, height);
	}

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double x, double y)
	{
		Liar::OpenGLWindow::runWindow->MouseEvent(window, x, y);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		/*if(Liar::Global::windowActive->GetHandler())
		{
		Liar::Global::windowActive->GetHandler()->ScrollEvent(xoffset, yoffset);
		}*/
	}

}
