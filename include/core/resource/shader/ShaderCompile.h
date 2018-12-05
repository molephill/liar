#pragma once

#include <core/resource/shader/ShaderDefine.h>

namespace Liar
{
	class ShaderCompile
	{
	public:
		ShaderCompile();
		~ShaderCompile();

	private:
		const char* GetShaderDefineChar(Liar::ShaderTypeDefine) const;
	};
}

