

#include <core/render/RenderState.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	RenderState::RenderState() :
		clientWidth(0), clientHeight(0),
		camera(nullptr), enableLight(true),
		shaderValue(new Liar::ShaderValue()), publicDefine(-1),
		stageContext(new Liar::StageContext()),
		lastCurrentTime(0), elapsedTime(0)
	{
	}

	RenderState::~RenderState()
	{
		camera = nullptr;
		delete shaderValue;
		shaderValue = nullptr;
		delete stageContext;
		stageContext = nullptr;
	}
}