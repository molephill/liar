
#include <Liar3D.h>

bool check_in_window(GLFWwindow* window, Liar::DNumber, Liar::DNumber);
void framebuffer_size_callback(GLFWwindow* window, Liar::Int width, Liar::Int height);
void mouse_callback(GLFWwindow* window, Liar::DNumber xpos, Liar::DNumber ypos);
void scroll_callback(GLFWwindow* window, Liar::DNumber xoffset, Liar::DNumber yoffset);

namespace Liar
{
	void Liar3D::Init(Liar::Int w, Liar::Int h, const Liar::Char* title)
	{
		glfwInit();

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);

		if (!window) {
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		Liar3D::vertexFactory = new Liar::VertexFactory();

		Liar3D::stageContext = new Liar::StageContext();

		Liar3D::renderState = new Liar::RenderState();

		Liar3D::stage = new Liar::Stage(w, h);

		Liar3D::Run(window, true);
	}

	void Liar3D::Run(GLFWwindow* window, bool run)
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

			run = Liar::Liar3D::stage->OnEnterFrame();
		}
		else
		{
			run = false;
		}
		Run(window, run);
	}

	void Liar3D::Destroy()
	{
		if (Liar::Liar3D::stage)
		{
			Liar::Liar3D::stage->~Stage();
			free(Liar::Liar3D::stage);
			Liar::Liar3D::stage = nullptr;
		}

		if (Liar::Liar3D::vertexFactory)
		{
			Liar::Liar3D::vertexFactory->~VertexFactory();
			free(vertexFactory);
			vertexFactory = nullptr;
		}

		if (Liar::Liar3D::stageContext)
		{
			Liar::Liar3D::stageContext->~StageContext();
			free(stageContext);
			stageContext = nullptr;
		}

		if (Liar::Liar3D::renderState)
		{
			Liar::Liar3D::renderState->~RenderState();
			free(Liar::Liar3D::renderState);
			Liar::Liar3D::renderState = nullptr;
		}
	}

	Liar::Stage* Liar3D::stage = nullptr;
	Liar::StageContext* Liar3D::stageContext = nullptr;
	Liar::VertexFactory* Liar3D::vertexFactory = nullptr;
	Liar::RenderState* Liar3D::renderState = nullptr;
}

// 判断是否在屏幕内
bool check_in_window(GLFWwindow* window, Liar::DNumber x, Liar::DNumber y)
{
	int sx = 0, sy = 0;
	int w = 0, h = 0;

	glfwGetWindowPos(window, &sx, &sy);
	glfwGetWindowSize(window, &w, &h);

	int ex = sx + w;
	int ey = sy + h;

	bool inWindow = x >= sx && x <= ex && y >= sy && y <= ey;
	return inWindow;
}

// 修改屏幕大小时
void framebuffer_size_callback(GLFWwindow* window, Liar::Int width, Liar::Int height)
{
	Liar::Liar3D::stage->SetSize(width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, Liar::DNumber x, Liar::DNumber y)
{
	bool inWindow = check_in_window(window, x, y);
	if (inWindow)
	{
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		Liar::Liar3D::stage->MouseEvent(x, y, state);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, Liar::DNumber x, Liar::DNumber y)
{
	bool inWindow = check_in_window(window, x, y);
	if (inWindow) Liar::Liar3D::stage->ScrollEvent(x, y);
}