#pragma once

#include <iostream>
#include "MathUtils3D.h"
#include "Quaternion.h"

namespace Liar
{
	class Vector3
	{
	public:
		Vector3(float sx = 0.0f, float sy = 0.0f, float sz = 0.0f) :x(sx), y(sy), z(sz) {};
		~Vector3() {};

	public:
		float x;
		float y;
		float z;

	public:
		inline static float DistanceSquared(const Liar::Vector3& value1, const Liar::Vector3& value2)
		{
			float tmpx = value1.x - value2.x;
			float tmpy = value1.y - value2.y;
			float tmpz = value1.z - value2.z;
			return tmpx * tmpx + tmpy * tmpy + tmpz * tmpz;
		}

		inline static float Distance(const Liar::Vector3& value1, const Liar::Vector3& value2)
		{
			float tmpx = value1.x - value2.x;
			float tmpy = value1.y - value2.y;
			float tmpz = value1.z - value2.z;
			return sqrtf(tmpx * tmpx + tmpy * tmpy + tmpz * tmpz);
		}

		inline static void Min(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out)
		{
			out.x = std::min(a.x, b.x);
			out.y = std::min(a.y, b.y);
			out.z = std::min(a.z, b.z);
		}

		inline static void Max(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out)
		{
			out.x = std::max(a.x, b.x);
			out.y = std::max(a.y, b.y);
			out.z = std::max(a.z, b.z);
		};

		static void TransformQuat(const Liar::Vector3& se, const Liar::Quaternion& re, Liar::Vector3& destination)
		{
			float x = se[0], y = se[1], z = se[2], qx = re[0], qy = re[1], qz = re[2], qw = re[3],
				ix = qw * x + qy * z - qz * y,
				iy = qw * y + qz * x - qx * z,
				iz = qw * z + qx * y - qy * x,
				iw = -qx * x - qy * y - qz * z;

			destination[0] = ix * qw + iw * -qx + iy * -qz - iz * -qy;
			destination[1] = iy * qw + iw * -qy + iz * -qx - ix * -qz;
			destination[2] = iz * qw + iw * -qz + ix * -qy - iy * -qx;
		};

		static float scalarLength(const Liar::Vector3& f)
		{
			return sqrt(f.x*f.x + f.y*f.y + f.z*f.z);
		};

		static float scalarLengthSquared(const Liar::Vector3& f)
		{
			return f.x*f.x + f.y*f.y + f.z*f.z;
		};

		static void Normalize(const Liar::Vector3& se, Liar::Vector3& oe)
		{
			float len = se.x*se.x + se.y*se.y + se.z*se.z;
			if (len > 0)
			{
				len = 1.0 / sqrt(len);
				oe[0] = se[0] * len;
				oe[1] = se[1] * len;
				oe[2] = se[2] * len;
			}
		};

		static void Multiply(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e)
		{
			e[0] = f[0] * g[0];
			e[1] = f[1] * g[1];
			e[2] = f[2] * g[2];
		};

		static void Scale(const Liar::Vector3& f, const float b, Liar::Vector3& e)
		{
			e[0] = f[0] * b;
			e[1] = f[1] * b;
			e[2] = f[2] * b;
		};

		static void Lerp(const Liar::Vector3& f, const Liar::Vector3& g, const float t, Liar::Vector3& e)
		{
			float ax = f.x, ay = f.y, az = f.z;
			e[0] = ax + t * (g[0] - ax);
			e[1] = ay + t * (g[1] - ay);
			e[2] = az + t * (g[2] - az);
		};

		static void TransformV3ToV4(const Liar::Vector3& vectorElem, const Liar::Matrix4x4& transformElem, Liar::Vector4& resultElem)
		{
			float vectorX = vectorElem[0], vectorY = vectorElem[1], vectorZ = vectorElem[2];

			resultElem[0] = (vectorX * transformElem[0]) + (vectorY * transformElem[4]) + (vectorZ * transformElem[8]) + transformElem[12];
			resultElem[1] = (vectorX * transformElem[1]) + (vectorY * transformElem[5]) + (vectorZ * transformElem[9]) + transformElem[13];
			resultElem[2] = (vectorX * transformElem[2]) + (vectorY * transformElem[6]) + (vectorZ * transformElem[10]) + transformElem[14];
			resultElem[3] = (vectorX * transformElem[3]) + (vectorY * transformElem[7]) + (vectorZ * transformElem[11]) + transformElem[15];
		};

		/**
		* 通过矩阵转换一个三维向量到另外一个三维向量。
		* @param	vector 源三维向量。
		* @param	transform  变换矩阵。
		* @param	result 输出三维向量。
		*/
		static void TransformV3ToV3(const Liar::Vector3& vector, const Liar::Matrix4x4& transform, Liar::Vector3& result)
		{
			Liar::Vector3::TransformV3ToV4(vector, transform, Liar::MathUtils3D::TEMPVector4);
			result[0] = Liar::MathUtils3D::TEMPVector4[0];
			result[1] = Liar::MathUtils3D::TEMPVector4[1];
			result[2] = Liar::MathUtils3D::TEMPVector4[2];
		}

		static void TransfromNormal(const Liar::Vector3& normalElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
		{
			float normalX = normalElem.x, normalY = normalElem.y, normalZ = normalElem.z;

			resultElem[0] = (normalX * transformElem[0]) + (normalY * transformElem[4]) + (normalZ * transformElem[8]);
			resultElem[1] = (normalX * transformElem[1]) + (normalY * transformElem[5]) + (normalZ * transformElem[9]);
			resultElem[2] = (normalX * transformElem[2]) + (normalY * transformElem[6]) + (normalZ * transformElem[10]);
		};

		static void TransformCoordinate(const Liar::Vector3& coordinateElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
		{
			float coordinateX = coordinateElem.x, coordinateY = coordinateElem.y, coordinateZ = coordinateElem.z;

			Liar::Vector4 vectorElem;
			vectorElem[0] = (coordinateX * transformElem[0]) + (coordinateY * transformElem[4]) + (coordinateZ * transformElem[8]) + transformElem[12];
			vectorElem[1] = (coordinateX * transformElem[1]) + (coordinateY * transformElem[5]) + (coordinateZ * transformElem[9]) + transformElem[13];
			vectorElem[2] = (coordinateX * transformElem[2]) + (coordinateY * transformElem[6]) + (coordinateZ * transformElem[10]) + transformElem[14];
			vectorElem[3] = 1.0 / ((coordinateX * transformElem[3]) + (coordinateY * transformElem[7]) + (coordinateZ * transformElem[11]) + transformElem[15]);

			resultElem[0] = vectorElem[0] * vectorElem[3];
			resultElem[1] = vectorElem[1] * vectorElem[3];
			resultElem[2] = vectorElem[2] * vectorElem[3];
		};

		static void Clamp(const Liar::Vector3& valuee, const Liar::Vector3& mine, const Liar::Vector3& maxe, Liar::Vector3& oute)
		{
			float x = valuee.x, y = valuee.y, z = valuee.z;
			float mineX = mine.x, mineY = mine.y, mineZ = mine.z;
			float maxeX = maxe.x, maxeY = maxe.y, maxeZ = maxe.z;

			x = (x > maxeX) ? maxeX : x;
			x = (x < mineX) ? mineX : x;

			y = (y > maxeY) ? maxeY : y;
			y = (y < mineY) ? mineY : y;

			z = (z > maxeZ) ? maxeZ : z;
			z = (z < mineZ) ? mineZ : z;

			oute[0] = x;
			oute[1] = y;
			oute[2] = z;
		};

		static void Add(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e)
		{
			e[0] = f[0] + g[0];
			e[1] = f[1] + g[1];
			e[2] = f[2] + g[2];
		};

		static void Subtract(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe)
		{
			oe[0] = ae[0] - be[0];
			oe[1] = ae[1] - be[1];
			oe[2] = ae[2] - be[2];
		};

		static void Cross(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe)
		{
			float ax = ae.x, ay = ae.y, az = ae.z,
				bx = be.x, by = be.y, bz = be.z;
			oe[0] = ay * bz - az * by;
			oe[1] = az * bx - ax * bz;
			oe[2] = ax * by - ay * bx;
		};

		static float Dot(const Liar::Vector3& ae, const Liar::Vector3& be)
		{
			return (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]);
		};

		static bool Equals(const Liar::Vector3& ae, const Liar::Vector3& be)
		{
			return MathUtils3D::NearEqual(abs(ae[0]), abs(be[0])) && MathUtils3D::NearEqual(abs(ae[1]), abs(be[1])) && MathUtils3D::NearEqual(abs(ae[2]), abs(be[2]));
		}

	public:
		friend Liar::Vector3 operator*(const float, const Liar::Vector3&);
		friend std::ostream& operator<<(std::ostream&, const Liar::Vector3&);

	public:
		inline void Set(float sx, float sy, float sz)
		{
			x = sx;
			y = sy;
			z = sz;
		};

		inline void Set(const Liar::Vector3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		};

		inline float Distance(const Liar::Vector3& rhs) const
		{
			return Distance(rhs.x, rhs.y, rhs.z);
		};

		inline float  Distance(float sx, float sy, float sz) const
		{
			float tmpx = x - sx;
			float tmpy = y - sy;
			float tmpz = z - sz;
		};

		inline Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		};

		inline Vector3 operator+(const Liar::Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		};

		inline Vector3 operator-(const Liar::Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		};

		inline Vector3& operator+=(const Liar::Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		};

		inline Vector3& operator-=(const Liar::Vector3 & rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		};

		inline Vector3 operator*(const float a) const
		{
			return Vector3(x*a, y*a, z*a);
		};

		inline Vector3& operator*=(float a)
		{
			x *= a;
			y *= a;
			z *= a;
			return *this;
		};

		inline Vector3 operator*(const Liar::Vector3& rhs)
		{
			return Vector3(x*rhs.x, y*rhs.y, z*rhs.z);
		}

		inline Vector3& operator*=(const Liar::Vector3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		};

		inline Vector3 operator/(const float a) const
		{
			return Vector3(x / a, y / a, z / a);
		};

		inline Vector3& operator/=(const float a)
		{
			x /= a;
			y /= a;
			z /= a;
			return *this;
		};

		inline Vector3 operator/(const Liar::Vector3& rhs) const
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		};

		inline Vector3& operator/=(const Liar::Vector3& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		};

		inline bool operator==(const float a) const
		{
			return x == a && y == a && z == a;
		};

		inline bool operator==(const Liar::Vector3& rhs) const
		{
			return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
		};

		inline bool operator!=(const float a) const
		{
			return (x != a) || (y != a) || (z != a);
		};

		inline bool operator!=(const Liar::Vector3& rhs)
		{
			return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
		};

		inline bool operator<(const Liar::Vector3& rhs)
		{
			if (x < rhs.x || y < rhs.y || z < rhs.z) return true;
			return false;
		};

		inline bool operator<=(const Liar::Vector3& rhs)
		{
			if (x <= rhs.x || y <= rhs.y || z <= rhs.z) return true;
			return false;
		};

		inline bool operator>(const Liar::Vector3& rhs)
		{
			if (x > rhs.x || y > rhs.y || z > rhs.z) return true;
			return false;
		};

		inline bool operator>=(const Liar::Vector3& rhs)
		{
			if (x >= rhs.x || y >= rhs.y || z >= rhs.z) return true;
			return false;
		};

		inline float operator[](size_t index) const
		{
			return (&x)[index];
		};

		inline float& operator[](size_t index)
		{
			return (&x)[index];
		};

		inline float Length() const
		{
			return sqrtf(x*x + y * y + z * z);
		};

		inline float Distance(const Vector3& rhs) const
		{
			return Distance(rhs.x, rhs.y, rhs.z);
		};

		inline float Distance(float cx, float cy, float cz) const
		{
			float tmpx = x - cx;
			float tmpy = y - cy;
			float tmpz = z - cz;
			return sqrtf(tmpx*tmpx + tmpy * tmpy + tmpz * tmpz);
		};

		inline Vector3& Normalize()
		{
			float xxyyzz = x * x + y * y + z * z;
			float invLength = 1.0f / sqrtf(xxyyzz);
			x *= invLength;
			y *= invLength;
			z *= invLength;
			return *this;
		};

		inline float Dot(float cx, float cy, float cz) const
		{
			return (x*cx + y * cy + z * cz);
		};

		inline float Dot(const Liar::Vector3& rhs) const
		{
			return Dot(rhs.x, rhs.y, rhs.z);
		};

		inline Vector3 Cross(float cx, float cy, float cz) const
		{
			return Vector3(y*cz - z * cy, z*cx - x * cz, x*cy - y * cx);
		};

		inline Vector3 Cross(const Liar::Vector3& rhs) const
		{
			return Cross(rhs.x, rhs.y, rhs.z);
		};

		inline bool Equal(float cx, float cy, float cz, float epsilon = Liar::MathUtils3D::ZERO_TO_LERANCE) const
		{
			return fabs(x - cx) < epsilon && fabs(y - cy) < epsilon && fabs(z - cz) < epsilon;
		};

		inline bool Equal(const Liar::Vector3& rhs, float e)
		{
			return Equal(rhs.x, rhs.y, rhs.z, e);
		};

	};

	inline Liar::Vector3 operator*(const float a, const Liar::Vector3& rhs)
	{
		return Vector3(a*rhs.x, a*rhs.y);
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector3& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
		return os;
	};
}

