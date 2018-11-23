#pragma once

#include "MathUtils3D.h"
#include <math/Vector3.h>

namespace Liar
{
	class Plane
	{
	public:
		Plane(Liar::Number d = 0):
			m_normal((Liar::Vector3*)malloc(sizeof(Liar::Vector3))),
			m_distance(d)
		{};

		~Plane()
		{
			free(m_normal);
			m_normal = nullptr;
		};

	private:
		Liar::Vector3* m_normal;
		Liar::Number m_distance;

	public:
		static Liar::Plane* CreatePlaneBy3P(const Liar::Vector3& point1e, const Liar::Vector3& point2e, const Liar::Vector3& point3e)
		{
			Liar::Number x1 = point2e[0] - point1e[0];
			Liar::Number y1 = point2e[1] - point1e[1];
			Liar::Number z1 = point2e[2] - point1e[2];
			Liar::Number x2 = point3e[0] - point1e[0];
			Liar::Number y2 = point3e[1] - point1e[1];
			Liar::Number z2 = point3e[2] - point1e[2];
			Liar::Number yz = (y1 * z2) - (z1 * y2);
			Liar::Number xz = (z1 * x2) - (x1 * z2);
			Liar::Number xy = (x1 * y2) - (y1 * x2);
			Liar::Number invPyth = 1 / (sqrtf((yz * yz) + (xz * xz) + (xy * xy)));

			Liar::Number x = yz * invPyth;
			Liar::Number y = xz * invPyth;
			Liar::Number z = xy * invPyth;

			Liar::Vector3& TEMPVec3e = Liar::MathUtils3D::TEMPVector30;
			TEMPVec3e[0] = x;
			TEMPVec3e[1] = y;
			TEMPVec3e[2] = z;

			Liar::Number d = -((x * point1e[0]) + (y * point1e[1]) + (z * point1e[2]));

			Liar::Plane* plane = (Liar::Plane*)malloc(sizeof(Liar::Plane));
			plane->SetNormal(TEMPVec3e);
			plane->SetDistance(d);
			return plane;
		};

		/**
		* 更改平面法线向量的系数，使之成单位长度。
		*/
		inline void Normalize()
		{
			Liar::Number normalEX = m_normal->x;
			Liar::Number normalEY = m_normal->y;
			Liar::Number normalEZ = m_normal->z;
			Liar::Number magnitude = 1 / sqrtf(normalEX * normalEX + normalEY * normalEY + normalEZ * normalEZ);

			m_normal[0] = normalEX * magnitude;
			m_normal[1] = normalEY * magnitude;
			m_normal[2] = normalEZ * magnitude;

			m_distance *= magnitude;
		}

		void SetNormal(const Liar::Vector3& rhs) { m_normal->Set(rhs); };
		void SetDistance(Liar::Number value) { m_distance = value; };
	};
}