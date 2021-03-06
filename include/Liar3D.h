#pragma once

#include <LiarType.h>
#include <core/display/Stage.hpp>
#include <core/render/StageContext.h>
#include <core/resource/shader/ShaderCompile.h>
#include <core/render/RenderState.h>
#include <utils/URL.h>
#include <core/render/Renderer.h>
#include <core/events/EventController.h>
#include <utils/CameraMoveScript.h>
#include <core/resource/MTL.h>
#include <math/ByteArray.h>

namespace Liar
{
	static const Liar::Number WINDOW_W = 960;
	static const Liar::Number WINDOW_H = 600;

	class Liar3D
	{
	public:
		Liar3D()
		{};
		~Liar3D()
		{};

	private:
		static GLFWwindow* m_window;
		static void Destroy();

	public:
		static Liar::Stage* stage;
		static Liar::RenderState* renderState;
		static Liar::ShaderCompile* shaderCompile;
		static Liar::URL* urlFormat;
		static Liar::RenderUnit** m_renderUnits;
		static Liar::Uint m_numberRenderUnit;
		static Liar::Uint m_curIndexRenderUnit;
		static Liar::Renderer* rendering;
		static Liar::EventController* events;
		static Liar::CameraMoveScript* cameraMoveScript;
		static Liar::MTL* mtl;
		static Liar::TickRender* tickRender;

	public:
		static void Init(Liar::Int w = Liar::WINDOW_W, Liar::Int h = Liar::WINDOW_H, const Liar::Char* title = "LiarOpenGL");
		static void Run();
		static Liar::ByteArray* LiarLoad(const char*, const char* = "rb");
		static void* ParseVector(Liar::ByteArray*, Liar::VertexFormatType);
		static Liar::VertexFormatType ElementAttrFormat(Liar::VertexElementAttr);
		static clock_t GetTimer();
		static Liar::Boolen CheckTimeout(Liar::Int);
	};
}