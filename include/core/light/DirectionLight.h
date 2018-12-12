#pragma once

#include "BaseLight.h"
#include <core/display/Transform3D.h>

namespace Liar
{
	class DirectionLight:public Liar::BaseLight
	{
	public:
		DirectionLight();
		virtual ~DirectionLight();

	private:
		Liar::Vector3* m_direction;
		Liar::Transform3D* m_transform3d;

	public:
		void SetDirection(const Liar::Vector3& rhs) { m_direction->Set(rhs); };
		void SetDirection(Liar::Number x, Liar::Number y, Liar::Number z) { m_direction->Set(x, y, z); };
		Liar::Vector3& GetDirection() const { return *m_direction; };

	public:
		void SetShadow(bool) {};
		virtual bool Destroy(bool destroyChild = true);
		virtual bool PrepareRender(Liar::RenderState&);
	};
}