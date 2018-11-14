#pragma once

#include <iostream>
#include "MathUtils3D.h"

namespace Liar
{
	class Vector4
	{
	public:
		Vector4(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number cz = 0.0f, Liar::Number cw = 0.0f) :x(cx), y(cy), z(cz), w(cw) {};
		virtual ~Vector4() {};

	public:
		Liar::Number x;
		Liar::Number y;
		Liar::Number z;
		Liar::Number w;

	public:
		static void Lerp(Liar::Vector4& a, Liar::Vector4& b, Liar::Number t, Liar::Vector4& out)
		{
			Liar::Number ax = a.x, ay = a.y, az = a.z, aw = a.w;
			out.x = ax + t * (b.x - ax);
			out.y = ay + t * (b.y - ay);
			out.z = az + t * (b.z - az);
			out.w = aw + t * (b.w - aw);
		};

		static bool Equals(const Liar::Vector4& ae, const Liar::Vector4& be)
		{
			return MathUtils3D::NearEqual(abs(ae[0]), abs(be[0])) && 
				MathUtils3D::NearEqual(abs(ae[1]), abs(be[1])) && 
				MathUtils3D::NearEqual(abs(ae[2]), abs(be[2])) && 
				MathUtils3D::NearEqual(abs(ae[3]), abs(be[3]));
		};

		static void Normalize(const Liar::Vector4& se, Liar::Vector4& oe)
		{
			Liar::Number len = se.Length();
			if (len > 0)
			{
				oe[0] = se[0] * len;
				oe[1] = se[1] * len;
				oe[2] = se[2] * len;
				oe[3] = se[3] * len;
			}
		};

		static void Add(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
		{
			oe[0] = ae[0] + be[0];
			oe[1] = ae[1] + be[1];
			oe[2] = ae[2] + be[2];
			oe[3] = ae[3] + be[3];
		};

		static void Subtract(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
		{
			oe[0] = ae[0] - be[0];
			oe[1] = ae[1] - be[1];
			oe[2] = ae[2] - be[2];
			oe[3] = ae[3] - be[3];
		};

		static void Multiply(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
		{
			oe[0] = ae[0] * be[0];
			oe[1] = ae[1] * be[1];
			oe[2] = ae[2] * be[2];
			oe[3] = ae[3] * be[3];
		};

		static void Scale(const Liar::Vector4& ae, const Liar::Number b, Liar::Vector4& oe)
		{
			oe[0] = ae[0] * b;
			oe[1] = ae[1] * b;
			oe[2] = ae[2] * b;
			oe[3] = ae[3] * b;
		};

		static void Clamp(const Liar::Vector4& valuee, const Liar::Vector4& mine, const Liar::Vector4& maxe, Liar::Vector4& oute)
		{
			Liar::Number x = valuee[0], y = valuee[1], z = valuee[2], w = valuee[3];
			Liar::Number mineX = mine[0], mineY = mine[1], mineZ = mine[2], mineW = mine[3];
			Liar::Number maxeX = maxe[0], maxeY = maxe[1], maxeZ = maxe[2], maxeW = maxe[3];

			x = (x > maxeX) ? maxeX : x;
			x = (x < mineX) ? mineX : x;

			y = (y > maxeY) ? maxeY : y;
			y = (y < mineY) ? mineY : y;

			z = (z > maxeZ) ? maxeZ : z;
			z = (z < mineZ) ? mineZ : z;

			w = (w > maxeW) ? maxeW : w;
			w = (w < mineW) ? mineW : w;

			oute[0] = x;
			oute[1] = y;
			oute[2] = z;
			oute[3] = w;
		}

		static Liar::Number DistanceSquared(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
		{
			Liar::Number x = value1e[0] - value2e[0];
			Liar::Number y = value1e[1] - value2e[1];
			Liar::Number z = value1e[2] - value2e[2];
			Liar::Number w = value1e[3] - value2e[3];

			return (x * x) + (y * y) + (z * z) + (w * w);
		};

		static Liar::Number Distatnce(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
		{
			Liar::Number x = value1e[0] - value2e[0];
			Liar::Number y = value1e[1] - value2e[1];
			Liar::Number z = value1e[2] - value2e[2];
			Liar::Number w = value1e[3] - value2e[3];

			return sqrt((x * x) + (y * y) + (z * z) + (w * w));
		}

		static Liar::Number Dot(const Liar::Vector4& ae, const Liar::Vector4& be)
		{
			return (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]) + (ae[3] * be[3]);
		};

		static void Min(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e)
		{
			e[0] = std::min(f[0], g[0]);
			e[1] = std::min(f[1], g[1]);
			e[2] = std::min(f[2], g[2]);
			e[3] = std::min(f[3], g[3]);
		};

		static void Max(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e)
		{
			e[0] = std::max(f[0], g[0]);
			e[1] = std::max(f[1], g[1]);
			e[2] = std::max(f[2], g[2]);
			e[3] = std::max(f[3], g[3]);
		};

	public:
		friend Vector4 operator*(const Liar::Number, const Vector4&);
		friend std::ostream& operator<<(std::ostream&, const Vector4&);

	public:
		inline void Set(Liar::Number cx, Liar::Number cy, Liar::Number cz, Liar::Number cw)
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
				Liar::Number len = 1.0f / sqrtf(len);
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

