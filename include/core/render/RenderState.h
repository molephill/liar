#pragma once

#include <LiarType.h>
#include <core/resource/shader/ShaderValue.h>
#include <core/render/StageContext.h>
#include <core/resource/shader/ShaderProgram.h>

namespace Liar
{
	class BaseCamera;

	class RenderState
	{
	public:
		RenderState();
		~RenderState();

	public:
		Liar::Uint clientWidth;
		Liar::Uint clientHeight;
		Liar::BaseCamera* camera;
		bool enableLight;
		Liar::ShaderValue* shaderValue;
		Liar::Int publicDefine;
		Liar::StageContext* stageContext;
		Liar::Int lastCurrentTime;
		Liar::Int elapsedTime;
	};
}