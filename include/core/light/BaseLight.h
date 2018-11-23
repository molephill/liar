#pragma once

#include <core/display/Node.h>
#include <math/Vector3.h>

namespace Liar
{
	class BaseLight :public Node
	{
	public:
		BaseLight();
		virtual ~BaseLight();

	protected:
		Liar::Vector3* m_color;					// 灯光颜色 
		Liar::Vector3* m_ambient;				// 材料的环境光颜色
		Liar::Vector3* m_diffuse;				// 材料的漫反射光颜色
		Liar::Vector3* m_specular;				// 材料的镜面反射光颜色
		bool m_shadow;

	public:
		Liar::Vector3& GetColor() const { return *m_color; };
		Liar::Vector3& GetAmbient() const { return *m_ambient; };
		Liar::Vector3& GetDiffuse() const { return *m_diffuse; };
		Liar::Vector3& GetSpecular() const { return *m_specular; };

		void SetColor(const Liar::Vector3& rhs) { m_color->Set(rhs); };
		void SetColor(Liar::Number r, Liar::Number g, Liar::Number b) { m_color->Set(r, g, b); };
		void SetAmbient(const Liar::Vector3& rhs) { m_ambient->Set(rhs); };
		void SetAmbient(Liar::Number a, Liar::Number b, Liar::Number c) { m_ambient->Set(a, b, c); };
		void SetDiffuse(const Liar::Vector3& rhs) { m_diffuse->Set(rhs); };
		void SetDiffuse(Liar::Number a, Liar::Number b, Liar::Number c) { m_diffuse->Set(a, b, c); };
		void SetSpecular(const Liar::Vector3& rhs) { m_specular->Set(rhs); };
		void SetSpecular(Liar::Number a, Liar::Number b, Liar::Number c) { m_specular->Set(a, b, c); };

	public:
		bool GetShadow() const { return m_shadow; };
		virtual void SetShadow(bool) = 0;
		
	public:
		virtual bool Destroy(bool destroyChild = true);
	};
}