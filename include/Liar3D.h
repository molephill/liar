#pragma once

#include <LiarType.h>
#include <core/display/Stage.hpp>
#include <core/render/StageContext.h>
#include <core/render/RenderState.h>
#include <core/models/GeometryFactory.h>

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
		static Liar::StageContext* stageContext;
		static Liar::RenderState* renderState;
		static Liar::GeometryFactory* geometryFactory;

	public:
		static void Init(Liar::Int w = Liar::WINDOW_W, Liar::Int h = Liar::WINDOW_H, const Liar::Char* title = "LiarOpenGL");
		static bool Run(bool run = true);
	};	
}