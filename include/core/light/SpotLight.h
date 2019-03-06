#pragma once

#include "PointLight.h"

namespace Liar
{
	class SpotLight :public Liar::PointLight
	{
	public:
		SpotLight();
		virtual ~SpotLight();

	private:
		Liar::Vector3* m_direction;
		Liar::Number m_spot;					// 聚光的聚光值

	public:
		void SetDirection(const Liar::Vector3& rhs) { m_direction->Set(rhs); };
		void SetDirection(Liar::Number x, Liar::Number y, Liar::Number z) { m_direction->Set(x, y, z); };
		Liar::Vector3& GetDirection() const { return *m_direction; };

		void SetSpot(Liar::Number value) { m_spot = value; };
		Liar::Number GetSpot() const { return m_spot; };

		virtual bool PrepareRender(Liar::RenderState&);
	};
}