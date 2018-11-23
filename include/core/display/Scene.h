#pragma once

#include <core/display/TransformNode.h>
#include <core/render/BaseCamera.h>

namespace Liar
{
	class Scene:public TransformNode
	{
	public:
		Scene();
		virtual ~Scene();

	private:
		Liar::BaseCamera** m_cameras;
		Liar::Uint m_numberCamera;

	public:
		bool Render();
	};
}