#pragma once

#include <iostream>
#include "MathUtils3D.h"

namespace Liar
{
	class Vector4
	{
	public:
		Vector4(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number cz = 0.0f, Liar::Number cw = 0.0f) { Set(cx, cy, cz, cw); };
		virtual ~Vector4() {};

	public:
		Liar::Number x;
		Liar::Number y;
		Liar::Number z;
		Liar::Number w;

	public:
		static void Lerp(Liar::Vector4& a, Liar::Vector4& b, Liar::Number t, Liar::Vector4& out);
		static bool Equals(const Liar::Vector4& ae, const Liar::Vector4& be);
		static void Normalize(const Liar::Vector4& se, Liar::Vector4& oe);
		static void Add(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe);
		static void Subtract(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe);
		static void Multiply(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe);
		static void Scale(const Liar::Vector4& ae, const Liar::Number b, Liar::Vector4& oe);
		static void Clamp(const Liar::Vector4& valuee, const Liar::Vector4& mine, const Liar::Vector4& maxe, Liar::Vector4& oute);
		static Liar::Number DistanceSquared(const Liar::Vector4& value1e, const Liar::Vector4& value2e);
		static Liar::Number Distatnce(const Liar::Vector4& value1e, const Liar::Vector4& value2e);
		static Liar::Number Dot(const Liar::Vector4& ae, const Liar::Vector4& be);
		static void Min(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e);
		static void Max(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e);
		static void TransformByM4x4(const Liar::Vector4&, const Liar::Matrix4x4&, Liar::Vector4&);

	public:
		friend Vector4 operator*(const Liar::Number, const Vector4&);
		friend std::ostream& operator<<(std::ostream&, const Vector4&);

	public:
		inline void Set(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number cz = 0.0f, Liar::Number cw = 0.0f)
		{
			x = cx;
			y = cy;
			z = cz;
			w = cw;
		};

		inline void Set(const Liar::Vector4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		};

		inline Vector4 operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		};

		inline Vector4 operator+(const Liar::Vector4& rhs)
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		};

		inline Vector4& operator+=(const Liar::Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		};

		inline Vector4 operator-(const Liar::Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		};

		inline Vector4 operator-=(const Liar::Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		};

		inline Vector4 operator*(const Liar::Vector4& rhs) const
		{
			return Vector4(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
		};

		inline Vector4& operator*=(const Liar::Vector4& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
			return *this;
		};

		inline Vector4 operator*(const Liar::Number a) const
		{
			return Vector4(x*a, y*a, z*a, w*a);
		};

		inline Vector4& operator*=(const Liar::Number a)
		{
			x *= a;
			y *= a;
			z *= a;
			w *= a;
			return *this;
		};

		inline Vector4 operator/(const Liar::Vector4& rhs) const
		{
			return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		};

		inline Vector4& operator/=(const Liar::Vector4& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		};

		inline Vector4 operator/(const Liar::Number a) const
		{
			return Vector4(x / a, y / a, z / a, w / a);
		};

		inline Vector4& operator/=(const Liar::Number a)
		{
			x /= a;
			y /= a;
			z /= a;
			w /= a;
			return *this;
		};

		inline bool operator==(const Liar::Number a) const
		{
			return (x == a) && (y == a) && (z == a) && (w == a);
		};

		inline bool operator==(const Liar::Vector4& rhs) const
		{
			return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
		};

		inline bool operator!=(const Liar::Number a) const
		{
			return (x != a) || (y != a) || (z != a) || (w != a);
		};

		inline bool operator!=(const Liar::Vector4& rhs) const
		{
			return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
		};

		inline bool operator<(const Liar::Vector4& rhs) const
		{
			if (x < rhs.x || y < rhs.y || z < rhs.z || w < rhs.z) return true;
			return false;
		};

		inline bool operator<=(const Liar::Vector4& rhs) const
		{
			if (x <= rhs.x || y <= rhs.y || z <= rhs.z || w <= rhs.z) return true;
			return false;
		};

		inline bool operator>(const Liar::Vector4& rhs) const
		{
			return (x > rhs.x) || (y > rhs.y) || (z > rhs.z) || (w > rhs.w);
		};

		inline bool operator>=(const Liar::Vector4& rhs) const
		{
			return (x >= rhs.x) || (y >= rhs.y) || (z >= rhs.z) || (w >= rhs.w);
		};

		inline Liar::Number operator[](size_t index) const
		{
			return (&x)[index];
		};

		inline Liar::Number& operator[](size_t index)
		{
			return (&x)[index];
		};

		inline Liar::Number Distance(Liar::Number cx, Liar::Number cy, Liar::Number cz, Liar::Number cw) const
		{
			Liar::Number tmpx = x - cx;
			Liar::Number tmpy = y - cy;
			Liar::Number tmpz = z - cz;
			Liar::Number tmpw = w - cw;
			return sqrtf(tmpx*tmpx + tmpy * tmpy + tmpz * tmpz + tmpw * tmpw);
		};

		inline Liar::Number Distance(const Liar::Vector4& rhs) const
		{
			return Distance(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline Liar::Number Length() const
		{
			return sqrtf(x*x + y * y + z * z + w * w);
		};

		inline Liar::Number LengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		inline Vector4& Normalize()
		{
			Liar::Number xxyyzzww = x * x + y * y + z * z + w * w;
			if (xxyyzzww)
			{
				Liar::Number invLength = 1.0f / sqrtf(xxyyzzww);
				x *= invLength;
				y *= invLength;
				z *= invLength;
			}
			return *this;
		};

		inline void Normalize(Liar::Vector4& e)
		{
			Liar::Number xxyyzzww = x * x + y * y + z * z + w * w;
			if (xxyyzzww > 0) {
				Liar::Number len = 1.0f / sqrtf(xxyyzzww);
				e[0] = x * len;
				e[1] = y * len;
				e[2] = z * len;
				e[3] = w * len;
			}
		}

		inline Liar::Number Dot(Liar::Number cx, Liar::Number cy, Liar::Number cz, Liar::Number cw) const
		{
			return (x*cx + y * cy + z * cz + w * cw);
		};

		inline Liar::Number Dot(const Liar::Vector4& rhs) const
		{
			return Dot(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline bool Equal(Liar::Number cx, Liar::Number cy, Liar::Number cz, Liar::Number cw, Liar::Number epsilon = Liar::MathUtils3D::ZERO_TO_LERANCE) const
		{
			return fabs(x - cx) < epsilon && fabs(y - cy) < epsilon && fabs(z - cz) < epsilon && fabs(w - cw) < epsilon;
		};

		inline bool Equal(const Liar::Vector4& rhs) const
		{
			return Equal(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline Vector4& Scaling(Liar::Number scaling)
		{
			x *= scaling;
			y *= scaling;
			z *= scaling;
			w *= scaling;
			return *this;
		};

		inline void Scaling(Liar::Number scaling, Liar::Vector4& e)
		{
			e[0] = x * scaling;
			e[1] = y * scaling;
			e[2] = z * scaling;
			e[3] = w * scaling;
		};

		/**
		* 根据绕X轴的角度旋转四元数
		* @param	rad 角度
		* @param	out 输出四元数
		*/
		inline Vector4& RotateX(Liar::Number rad)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number bx = sinf(rad), bw = cosf(rad);
			x = ax * bw + aw * bx;
			y = ay * bw + az * bx;
			z = az * bw - ay * bx;
			w = aw * bw - ax * bx;
			return *this;
		};

		inline void RotateX(Liar::Number rad, Liar::Vector4& e)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number bx = sinf(rad), bw = cosf(rad);

			e[0] = ax * bw + aw * bx;
			e[1] = ay * bw + az * bx;
			e[2] = az * bw - ay * bx;
			e[3] = aw * bw - ax * bx;
		};

		/**
		* 根据绕Y轴的制定角度旋转四元数
		* @param	rad 角度
		* @param	out 输出四元数
		*/
		inline Vector4& RotateY(Liar::Number rad)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number by = sinf(rad), bw = cosf(rad);
			x = ax * bw - az * by;
			y = ay * bw + aw * by;
			z = az * bw + ax * by;
			w = aw * bw - ay * by;
			return *this;
		};

		inline void RotateY(Liar::Number rad, Liar::Vector4& e)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number by = sinf(rad), bw = cosf(rad);
			e[0] = ax * bw - az * by;
			e[1] = ay * bw + aw * by;
			e[2] = az * bw + ax * by;
			e[3] = aw * bw - ay * by;
		}

		/**
		* 根据绕Z轴的制定角度旋转四元数
		* @param	rad 角度
		* @param	out 输出四元数
		*/
		inline Vector4& RotateZ(Liar::Number rad)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number bz = sinf(rad), bw = cosf(rad);
			x = ax * bw + ay * bz;
			y = ay * bw - ax * bz;
			z = az * bw + aw * bz;
			w = aw * bw - az * bz;
			return *this;
		};

		inline void RotateZ(Liar::Number rad, Liar::Vector4& e)
		{
			Liar::Number ax = x, ay = y, az = z, aw = w;
			Liar::Number bz = sinf(rad), bw = cosf(rad);
			e[0] = ax * bw + ay * bz;
			e[1] = ay * bw - ax * bz;
			e[2] = az * bw + aw * bz;
			e[3] = aw * bw - az * bz;
		}
	};

	inline Vector4 operator*(const Liar::Number a, const Vector4& vec) {
		return Vector4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return os;
	}
}

