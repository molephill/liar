#pragma once

#include "MathUtils3D.h"

namespace Liar
{
	class Plane
	{
	public:
		Plane(Liar::Vector3& normal, float d = 0)
		{
			m_normal = new Liar::Vector3(normal);
			m_distance = d;
		};

		~Plane()
		{
			delete m_normal;
		};

	private:
		Liar::Vector3* m_normal;
		float m_distance;

	public:
		static Liar::Plane* CreatePlaneBy3P(const Liar::Vector3& point1e, const Liar::Vector3& point2e, const Liar::Vector3& point3e)
		{
			float x1 = point2e[0] - point1e[0];
			float y1 = point2e[1] - point1e[1];
			float z1 = point2e[2] - point1e[2];
			float x2 = point3e[0] - point1e[0];
			float y2 = point3e[1] - point1e[1];
			float z2 = point3e[2] - point1e[2];
			float yz = (y1 * z2) - (z1 * y2);
			float xz = (z1 * x2) - (x1 * z2);
			float xy = (x1 * y2) - (y1 * x2);
			float invPyth = 1 / (sqrtf((yz * yz) + (xz * xz) + (xy * xy)));

			float x = yz * invPyth;
			float y = xz * invPyth;
			float z = xy * invPyth;

			Liar::Vector3& TEMPVec3e = Liar::MathUtils3D::TEMPVector30;
			TEMPVec3e[0] = x;
			TEMPVec3e[1] = y;
			TEMPVec3e[2] = z;

			float d = -((x * point1e[0]) + (y * point1e[1]) + (z * point1e[2]));

			return new Plane(TEMPVec3e, d);
		};

		/**
		* 更改平面法线向量的系数，使之成单位长度。
		*/
		inline void Normalize()
		{
			float normalEX = m_normal->x;
			float normalEY = m_normal->y;
			float normalEZ = m_normal->z;
			float magnitude = 1 / sqrtf(normalEX * normalEX + normalEY * normalEY + normalEZ * normalEZ);

			m_normal[0] = normalEX * magnitude;
			m_normal[1] = normalEY * magnitude;
			m_normal[2] = normalEZ * magnitude;

			m_distance *= magnitude;
		}
	};
}