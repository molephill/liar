#pragma once

#include <iostream>
#include "MathUtils3D.h"

namespace Liar
{
	class Vector3
	{
	public:
		Vector3(Liar::Number sx = 0.0f, Liar::Number sy = 0.0f, Liar::Number sz = 0.0f) :x(sx), y(sy), z(sz) {};
		~Vector3() {};

	public:
		Liar::Number x;
		Liar::Number y;
		Liar::Number z;

	public:
		inline static Liar::Number DistanceSquared(const Liar::Vector3& value1, const Liar::Vector3& value2)
		{
			Liar::Number tmpx = value1.x - value2.x;
			Liar::Number tmpy = value1.y - value2.y;
			Liar::Number tmpz = value1.z - value2.z;
			return tmpx * tmpx + tmpy * tmpy + tmpz * tmpz;
		}

		inline static Liar::Number Distance(const Liar::Vector3& value1, const Liar::Vector3& value2)
		{
			Liar::Number tmpx = value1.x - value2.x;
			Liar::Number tmpy = value1.y - value2.y;
			Liar::Number tmpz = value1.z - value2.z;
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

		static Liar::Number scalarLength(const Liar::Vector3& f)
		{
			return sqrt(f.x*f.x + f.y*f.y + f.z*f.z);
		};

		static Liar::Number scalarLengthSquared(const Liar::Vector3& f)
		{
			return f.x*f.x + f.y*f.y + f.z*f.z;
		};

		static void Normalize(const Liar::Vector3& se, Liar::Vector3& oe)
		{
			Liar::Number len = se.x*se.x + se.y*se.y + se.z*se.z;
			if (len > 0)
			{
				len = static_cast<Liar::Number>(1.0 / sqrtf(len));
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

		static void Scale(const Liar::Vector3& f, const Liar::Number b, Liar::Vector3& e)
		{
			e[0] = f[0] * b;
			e[1] = f[1] * b;
			e[2] = f[2] * b;
		};

		static void Lerp(const Liar::Vector3& f, const Liar::Vector3& g, const Liar::Number t, Liar::Vector3& e)
		{
			Liar::Number ax = f.x, ay = f.y, az = f.z;
			e[0] = ax + t * (g[0] - ax);
			e[1] = ay + t * (g[1] - ay);
			e[2] = az + t * (g[2] - az);
		};

		static void Clamp(const Liar::Vector3& valuee, const Liar::Vector3& mine, const Liar::Vector3& maxe, Liar::Vector3& oute)
		{
			Liar::Number x = valuee.x, y = valuee.y, z = valuee.z;
			Liar::Number mineX = mine.x, mineY = mine.y, mineZ = mine.z;
			Liar::Number maxeX = maxe.x, maxeY = maxe.y, maxeZ = maxe.z;

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
			Liar::Number ax = ae.x, ay = ae.y, az = ae.z,
				bx = be.x, by = be.y, bz = be.z;
			oe[0] = ay * bz - az * by;
			oe[1] = az * bx - ax * bz;
			oe[2] = ax * by - ay * bx;
		};

		static Liar::Number Dot(const Liar::Vector3& ae, const Liar::Vector3& be)
		{
			return (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]);
		};

		static bool Equals(const Liar::Vector3& ae, const Liar::Vector3& be)
		{
			return MathUtils3D::NearEqual(abs(ae[0]), abs(be[0])) && MathUtils3D::NearEqual(abs(ae[1]), abs(be[1])) && MathUtils3D::NearEqual(abs(ae[2]), abs(be[2]));
		}

	public:
		friend Liar::Vector3 operator*(const Liar::Number, const Liar::Vector3&);
		friend std::ostream& operator<<(std::ostream&, const Liar::Vector3&);

	public:
		inline void Set(Liar::Number sx, Liar::Number sy, Liar::Number sz)
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

		inline Vector3 operator*(const Liar::Number a) const
		{
			return Vector3(x*a, y*a, z*a);
		};

		inline Vector3& operator*=(Liar::Number a)
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

		inline Vector3 operator/(const Liar::Number a) const
		{
			return Vector3(x / a, y / a, z / a);
		};

		inline Vector3& operator/=(const Liar::Number a)
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

		inline bool operator==(const Liar::Number a) const
		{
			return x == a && y == a && z == a;
		};

		inline bool operator==(const Liar::Vector3& rhs) const
		{
			return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
		};

		inline bool operator!=(const Liar::Number a) const
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

		inline Liar::Number operator[](size_t index) const
		{
			return (&x)[index];
		};

		inline Liar::Number& operator[](size_t index)
		{
			return (&x)[index];
		};

		inline Liar::Number Length() const
		{
			return sqrtf(x*x + y * y + z * z);
		};

		inline Liar::Number Distance(Liar::Number cx, Liar::Number cy, Liar::Number cz) const
		{
			Liar::Number tmpx = x - cx;
			Liar::Number tmpy = y - cy;
			Liar::Number tmpz = z - cz;
			return sqrtf(tmpx*tmpx + tmpy * tmpy + tmpz * tmpz);
		};

		inline Liar::Number Distance(const Vector3& rhs) const
		{
			return Distance(rhs.x, rhs.y, rhs.z);
		};

		inline Vector3& Normalize()
		{
			Liar::Number xxyyzz = x * x + y * y + z * z;
			Liar::Number invLength = 1.0f / sqrtf(xxyyzz);
			x *= invLength;
			y *= invLength;
			z *= invLength;
			return *this;
		};

		inline Liar::Number Dot(Liar::Number cx, Liar::Number cy, Liar::Number cz) const
		{
			return (x*cx + y * cy + z * cz);
		};

		inline Liar::Number Dot(const Liar::Vector3& rhs) const
		{
			return Dot(rhs.x, rhs.y, rhs.z);
		};

		inline Vector3 Cross(Liar::Number cx, Liar::Number cy, Liar::Number cz) const
		{
			return Vector3(y*cz - z * cy, z*cx - x * cz, x*cy - y * cx);
		};

		inline Vector3 Cross(const Liar::Vector3& rhs) const
		{
			return Cross(rhs.x, rhs.y, rhs.z);
		};

		inline bool Equal(Liar::Number cx, Liar::Number cy, Liar::Number cz, Liar::DNumber epsilon = Liar::MathUtils3D::ZERO_TO_LERANCE) const
		{
			return fabs(x - cx) < epsilon && fabs(y - cy) < epsilon && fabs(z - cz) < epsilon;
		};

		inline bool Equal(const Liar::Vector3& rhs, Liar::DNumber epsilon = Liar::MathUtils3D::ZERO_TO_LERANCE)
		{
			return Equal(rhs.x, rhs.y, rhs.z, epsilon);
		};


	};

	inline Liar::Vector3 operator*(const Liar::Number a, const Liar::Vector3& rhs)
	{
		return Vector3(a*rhs.x, a*rhs.y);
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector3& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
		return os;
	};
}

