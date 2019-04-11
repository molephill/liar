
#include <Liar3D.h>
#include <time.h>

bool check_in_window(GLFWwindow* window, Liar::DNumber, Liar::DNumber);
void framebuffer_size_callback(GLFWwindow* window, Liar::Int width, Liar::Int height);
void mouse_callback(GLFWwindow* window, Liar::DNumber xpos, Liar::DNumber ypos);
void scroll_callback(GLFWwindow* window, Liar::DNumber xoffset, Liar::DNumber yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

		Liar::Liar3D::m_window = window;

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		Liar::Liar3D::urlFormat = new Liar::URL();
#ifdef __APPLE__
#else
		Liar::Liar3D::urlFormat->basePath = "E:\\c++\\liar\\liar\\core\\";
		Liar::Liar3D::urlFormat->baseShaderFolder = "resource\\shader\\files\\";
		Liar::Liar3D::urlFormat->baseSourceFolder = "C:\\Users\\Administrator\\Desktop\\model\\";
		Liar::Liar3D::urlFormat->baseSkeletonFolder = "C:\\Users\\Administrator\\Desktop\\model\\skeletons\\";
#endif
		Liar::Liar3D::events = new Liar::EventController();
		Liar::Liar3D::mtl = new Liar::MTL();
		Liar::Liar3D::stage = new Liar::Stage(w, h);
		Liar::Liar3D::renderState = new Liar::RenderState();
		Liar::Liar3D::shaderCompile = new Liar::ShaderCompile();
		Liar::Liar3D::rendering = new Liar::Renderer();
		Liar::Liar3D::cameraMoveScript = new Liar::CameraMoveScript();
		Liar::Liar3D::tickRender = new Liar::TickRender();

		Liar::Liar3D::renderState->stageContext->Enable(GL_DEPTH_TEST);
	}

	void Liar3D::Run()
	{
		bool run = true;
		GLFWwindow* window = Liar::Liar3D::m_window;
		while (run)
		{
			if (!glfwWindowShouldClose(window))
			{
				glfwSwapBuffers(window);
				glfwPollEvents();

				Liar::RenderState& state = *(Liar::Liar3D::renderState);

				// calc runtime
				clock_t start = GetTimer();
				state.elapsedTime = state.lastCurrentTime > 0 ? start - state.lastCurrentTime : 0;
				state.lastCurrentTime = start;

				Liar::Liar3D::tickRender->Loop();
				run = Liar::Liar3D::stage->OnEnterFrame(state);
				state.publicDefine = state.shaderValue->GetShaderDefineValue();
				rendering->Render(state);

			}
			else
			{
				glfwSetWindowShouldClose(window, true);
				Liar::Liar3D::Destroy();
				run = false;
			}
		}
	}

	clock_t Liar3D::GetTimer()
	{
		return clock();
	}

	Liar::Boolen Liar3D::CheckTimeout(Liar::Int delSec)
	{
		Liar::RenderState& state = *(Liar::Liar3D::renderState);
		return (Liar::Liar3D::GetTimer() - state.lastCurrentTime >= delSec);
	}

	Liar::ByteArray* Liar3D::LiarLoad(const char* filename, const char* mode)
	{
		FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
		if (0 != fopen_s(&f, filename, mode))
			f = 0;
#else
		f = fopen(filename, mode);
#endif

		if (!f) return nullptr;

		long lSize;
		char* buffer;
		size_t result;

		/* 获取文件大小 */
		fseek(f, 0, SEEK_END);
		lSize = ftell(f);
		rewind(f);

		/* 分配内存存储整个文件 */
		//buffer = (char*)malloc(sizeof(char)*lSize);
		buffer = new char[lSize];

#if defined(_MSC_VER) && _MSC_VER >= 1400
		result = fread_s(buffer, lSize, 1, lSize, f);
#else
		result = fread(buffer, 1, lSize, pFile);
#endif
		fclose(f);
		if (result != lSize) return nullptr;

		return Liar::ByteArray::CreateWithBuffer(buffer, lSize);
	}

	void* Liar3D::ParseVector(Liar::ByteArray* byte, Liar::VertexFormatType type)
	{
		switch (type)
		{
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2:
		{
			Liar::Vector2* vec = new Liar::Vector2();
			vec->x = byte->ReadFloat();
			vec->y = byte->ReadFloat();
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3:
		{
			Liar::Vector3* vec = new Liar::Vector3();
			vec->x = byte->ReadFloat();
			vec->y = byte->ReadFloat();
			vec->z = byte->ReadFloat();
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4:
		{
			Liar::Vector4* vec = new Liar::Vector4();
			vec->x = byte->ReadFloat();
			vec->y = byte->ReadFloat();
			vec->z = byte->ReadFloat();
			vec->w = byte->ReadFloat();
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION:
		{
			Liar::Quaternion* vec = new Liar::Quaternion();
			vec->x = byte->ReadFloat();
			vec->y = byte->ReadFloat();
			vec->z = byte->ReadFloat();
			vec->w = byte->ReadFloat();
			return vec;
		}
		default:
			return nullptr;
		}
	}

	Liar::VertexFormatType Liar3D::ElementAttrFormat(Liar::VertexElementAttr attrType)
	{
		Liar::VertexFormatType elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2;
		switch (attrType)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
		case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
		case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
		case Liar::VertexElementAttr::ELEMENT_ATTR_SCALE:
			elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION;
			break;
		default:
			elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4;
			break;
		}
		return elementType;
	}

	void Liar3D::Destroy()
	{
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

		if (Liar::Liar3D::rendering)
		{
			delete Liar::Liar3D::rendering;
			Liar::Liar3D::rendering = nullptr;
		}

		if (Liar::Liar3D::cameraMoveScript)
		{
			delete Liar::Liar3D::cameraMoveScript;
			Liar::Liar3D::cameraMoveScript = nullptr;
		}

		if (Liar::Liar3D::tickRender)
		{
			delete Liar::Liar3D::tickRender;
			Liar::Liar3D::tickRender = nullptr;
		}

		/*  放最后删除 */
		if (Liar::Liar3D::stage)
		{
			delete Liar::Liar3D::stage;
			Liar::Liar3D::stage = nullptr;
		}

		if (Liar::Liar3D::renderState)
		{
			delete Liar::Liar3D::renderState;
			Liar::Liar3D::renderState = nullptr;
		}

		if (Liar::Liar3D::events)
		{
			delete Liar::Liar3D::events;
			Liar::Liar3D::events = nullptr;
		}

		if (Liar::Liar3D::mtl)
		{
			delete Liar::Liar3D::mtl;
			Liar::Liar3D::mtl = nullptr;
		}

		glfwTerminate();
		Liar::Liar3D::m_window = nullptr;
	}

	Liar::Stage* Liar3D::stage = nullptr;
	Liar::RenderState* Liar3D::renderState = nullptr;
	Liar::ShaderCompile* Liar3D::shaderCompile = nullptr;
	Liar::URL* Liar3D::urlFormat = nullptr;
	Liar::Renderer* Liar3D::rendering = nullptr;
	Liar::EventController* Liar3D::events = nullptr;
	Liar::MTL* Liar3D::mtl = nullptr;
	Liar::CameraMoveScript* Liar3D::cameraMoveScript = nullptr;
	Liar::TickRender* Liar3D::tickRender = nullptr;
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

	bool inWindow = x >= 0 && x <= ex && y >= 0 && y <= ey;
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
		int state1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		int state2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		int state3 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
		bool mouseLDown = state1 == GLFW_PRESS;
		bool mouseRDown = state2 == GLFW_PRESS;
		bool mouseMDown = state3 == GLFW_PRESS;
		Liar::Liar3D::events->SetMouseEvent(static_cast<Liar::Number>(x), static_cast<Liar::Number>(y), 
			mouseLDown, mouseRDown, mouseMDown);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, Liar::DNumber x, Liar::DNumber y)
{
	Liar::Liar3D::events->ScrollMouseEvent(static_cast<Liar::Number>(x), static_cast<Liar::Number>(y));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		break;
	}
}