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
		Liar::Number m_cutOff;
		Liar::Number m_outerCutOff;

	public:
		void SetDirection(const Liar::Vector3& rhs) { m_direction->Set(rhs); };
		void SetDirection(Liar::Number x, Liar::Number y, Liar::Number z) { m_direction->Set(x, y, z); };
		Liar::Vector3& GetDirection() const { return *m_direction; };

		void SetCutOff(Liar::Number value) { m_cutOff = value; };
		void SetOuterCutoff(Liar::Number value) { m_outerCutOff = value; };

		Liar::Number GetCutOff() const { return m_cutOff; };
		Liar::Number GetOuterCutOff() const { return m_outerCutOff; };

		virtual bool Destroy(bool destroyChild = true);
	};
}