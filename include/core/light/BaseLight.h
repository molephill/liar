#pragma once

#include <math/Vector3.h>
#include <core/render/RenderState.h>

namespace Liar
{
	class BaseLight
	{
	public:
		BaseLight();
		virtual ~BaseLight();

	protected:
		Liar::Vector3* m_color;					// 灯光颜色 
		Liar::Number m_intensity;				// 强度
		bool m_shadow;

	public:
		Liar::Vector3& GetColor() const { return *m_color; };
		Liar::Number GetIntensity() const { return m_intensity; };

		void SetColor(const Liar::Vector3& rhs) { m_color->Set(rhs); };
		void SetColor(Liar::Number r, Liar::Number g, Liar::Number b) { m_color->Set(r, g, b); };
		void SetIntensity(Liar::Number value) { m_intensity = value; };

	public:
		bool GetShadow() const { return m_shadow; };
		virtual void SetShadow(bool) = 0;
		virtual bool Destroy(bool destroyChild = true);
		virtual bool PrepareRender(Liar::RenderState&) = 0;
	};
}