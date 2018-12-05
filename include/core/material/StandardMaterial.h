#pragma once

#include <core/material/BaseMaterial.h>

namespace Liar
{
	class StandardMaterial:public Liar::BaseMaterial
	{
	public:
		StandardMaterial();
		virtual ~StandardMaterial();

	public:
		virtual void SetRenderMode(Liar::RenderMode);
	};
}

