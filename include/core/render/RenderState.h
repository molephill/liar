#pragma once

#include <LiarType.h>
#include <core/resource/shader/ShaderValue.h>

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
	};
}