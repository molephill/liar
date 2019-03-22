#pragma once

#include <iostream>
#include "MathUtils3D.h"

namespace Liar
{
	class Vector3
	{
	public:
		Vector3(Liar::Number sx = Liar::ZERO, Liar::Number sy = Liar::ZERO, Liar::Number sz = Liar::ZERO) { Set(sx, sy, sz); };
		Vector3(const Liar::Vector3& rhs) { Set(rhs); };
		~Vector3() {};

	public:
		Liar::Number x;
		Liar::Number y;
		Liar::Number z;

	public:
		static Liar::Number DistanceSquared(const Liar::Vector3& value1, const Liar::Vector3& value2);
		static Liar::Number Distance(const Liar::Vector3& value1, const Liar::Vector3& value2);
		static void Min(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out);
		static void Max(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out);
		static Liar::Number ScalarLength(const Liar::Vector3& f);
		static Liar::Number ScalarLengthSquared(const Liar::Vector3& f);
		static void Normalize(const Liar::Vector3& se, Liar::Vector3& oe);
		static void Multiply(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e);
		static void Scale(const Liar::Vector3& f, const Liar::Number b, Liar::Vector3& e);
		static void Lerp(const Liar::Vector3& f, const Liar::Vector3& g, const Liar::Number t, Liar::Vector3& e);
		static void Clamp(const Liar::Vector3& valuee, const Liar::Vector3& mine, const Liar::Vector3& maxe, Liar::Vector3& oute);
		static void Add(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e);
		static void Subtract(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe);
		static void Cross(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe);
		static Liar::Number Dot(const Liar::Vector3& ae, const Liar::Vector3& be);
		static bool Equals(const Liar::Vector3& ae, const Liar::Vector3& be);

		static void TransformV3ToV4(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector4&);
		static void TransformV3ToV3(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransfromNormal(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransformCoordinate(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransformQuat(const Liar::Vector3&, const Liar::Quaternion&, Liar::Vector3&);

	public:
		friend Liar::Vector3 operator*(const Liar::Number, const Liar::Vector3&);
		friend std::ostream& operator<<(std::ostream&, const Liar::Vector3&);

	public:
		inline void Set(Liar::Number sx = Liar::ZERO, Liar::Number sy = Liar::ZERO, Liar::Number sz = Liar::ZERO)
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

