
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

		//glfwWindowHint(GLFW_SAMPLES, 4);
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

		Liar::Liar3D::m_window = window;

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		Liar::Liar3D::geometryFactory = new Liar::GeometryFactory();
		Liar::Liar3D::stageContext = new Liar::StageContext();
		Liar::Liar3D::renderState = new Liar::RenderState();
		Liar::Liar3D::stage = new Liar::Stage(w, h);
		Liar::Liar3D::shaderCompile = new Liar::ShaderCompile();
		Liar::Liar3D::urlFormat = new Liar::URL();

#ifdef __APPLE__
#else
		Liar::Liar3D::urlFormat->basePath = "E:\\c++\\liar\\liar\\core\\";
		Liar::Liar3D::urlFormat->baseshaderFolder = "resource\\shader\\files\\";
#endif
	}

	bool Liar3D::Run(bool runStatus)
	{
		if (!runStatus) return false;

		GLFWwindow* window = Liar::Liar3D::m_window;
		bool run = true;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();

			Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
			Liar::RenderState& state = *(Liar::Liar3D::renderState);

			run = Liar::Liar3D::stage->OnEnterFrame(gl, state);

		}
		else
		{
			glfwSetWindowShouldClose(window, true);
			Liar::Liar3D::Destroy();
			run = false;
		}
		return Run(run);
	}

	void Liar3D::Destroy()
	{
		if (Liar::Liar3D::stage)
		{
			delete Liar::Liar3D::stage;
			Liar::Liar3D::stage = nullptr;
		}

		if (Liar::Liar3D::geometryFactory)
		{
			delete Liar::Liar3D::geometryFactory;
			Liar::Liar3D::geometryFactory = nullptr;
		}

		if (Liar::Liar3D::stageContext)
		{
			delete Liar::Liar3D::stageContext;
			Liar::Liar3D::stageContext = nullptr;
		}

		if (Liar::Liar3D::renderState)
		{
			delete Liar::Liar3D::renderState;
			Liar::Liar3D::renderState = nullptr;
		}

		if (Liar::Liar3D::shaderCompile)
		{
			delete Liar::Liar3D::shaderCompile;
			Liar::Liar3D::shaderCompile = nullptr;
		}

		if (Liar::Liar3D::urlFormat)
		{
			delete Liar::Liar3D::urlFormat;
			Liar::Liar3D::urlFormat = nullptr;
		}

		glfwTerminate();
		Liar::Liar3D::m_window = nullptr;
	}

	Liar::Stage* Liar3D::stage = nullptr;
	Liar::StageContext* Liar3D::stageContext = nullptr;
	Liar::GeometryFactory* Liar3D::geometryFactory = nullptr;
	Liar::RenderState* Liar3D::renderState = nullptr;
	Liar::ShaderCompile* Liar3D::shaderCompile = nullptr;
	Liar::URL* Liar3D::urlFormat = nullptr;
	GLFWwindow* Liar3D::m_window = nullptr;
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