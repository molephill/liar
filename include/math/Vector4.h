#pragma once

#include <iostream>
#include "MathUtils3D.h"
#include "Matrix4x4.h"

namespace Liar
{
	class Vector4
	{
	public:
		Vector4(float cx = 0.0f, float cy = 0.0f, float cz = 0.0f, float cw = 0.0f) :x(cx), y(cy), z(cz), w(cw) {};
		virtual ~Vector4() {};

	public:
		float x;
		float y;
		float z;
		float w;

	public:
		static void Lerp(Liar::Vector4& a, Liar::Vector4& b, float t, Liar::Vector4& out)
		{
			float ax = a.x, ay = a.y, az = a.z, aw = a.w;
			out.x = ax + t * (b.x - ax);
			out.y = ay + t * (b.y - ay);
			out.z = az + t * (b.z - az);
			out.w = aw + t * (b.w - aw);
		};

		static void TransformByM4x4(const Liar::Vector4& ve, const Liar::Matrix4x4& me, Liar::Vector4& oe)
		{
			float vx = ve[0], vy = ve[1], vz = ve[2], vw = ve[3];
			oe[0] = vx * me[0] + vy * me[4] + vz * me[8] + vw * me[12];
			oe[1] = vx * me[1] + vy * me[5] + vz * me[9] + vw * me[13];
			oe[2] = vx * me[2] + vy * me[6] + vz * me[10] + vw * me[14];
			oe[3] = vx * me[3] + vy * me[7] + vz * me[11] + vw * me[15];
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
			float len = se.Length();
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

		static void Scale(const Liar::Vector4& ae, const float b, Liar::Vector4& oe)
		{
			oe[0] = ae[0] * b;
			oe[1] = ae[1] * b;
			oe[2] = ae[2] * b;
			oe[3] = ae[3] * b;
		};

		static void Clamp(const Liar::Vector4& valuee, const Liar::Vector4& mine, const Liar::Vector4& maxe, Liar::Vector4& oute)
		{
			float x = valuee[0], y = valuee[1], z = valuee[2], w = valuee[3];
			float mineX = mine[0], mineY = mine[1], mineZ = mine[2], mineW = mine[3];
			float maxeX = maxe[0], maxeY = maxe[1], maxeZ = maxe[2], maxeW = maxe[3];

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

		static float DistanceSquared(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
		{
			float x = value1e[0] - value2e[0];
			float y = value1e[1] - value2e[1];
			float z = value1e[2] - value2e[2];
			float w = value1e[3] - value2e[3];

			return (x * x) + (y * y) + (z * z) + (w * w);
		};

		static float Distatnce(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
		{
			float x = value1e[0] - value2e[0];
			float y = value1e[1] - value2e[1];
			float z = value1e[2] - value2e[2];
			float w = value1e[3] - value2e[3];

			return sqrt((x * x) + (y * y) + (z * z) + (w * w));
		}

		static float Dot(const Liar::Vector4& ae, const Liar::Vector4& be)
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
		friend Vector4 operator*(const float, const Vector4&);
		friend std::ostream& operator<<(std::ostream&, const Vector4&);

	public:
		inline void Set(float cx, float cy, float cz, float cw)
		{
			x = cx;
			y = cy;
			z = cz;
			w = cw;
		};

		inline void Set(Liar::Vector4& rhs)
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

		inline Vector4 operator*(const float a) const
		{
			return Vector4(x*a, y*a, z*a, w*a);
		};

		inline Vector4& operator*=(const float a)
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

		inline Vector4 operator/(const float a) const
		{
			return Vector4(x / a, y / a, z / a, w / a);
		};

		inline Vector4& operator/=(const float a)
		{
			x /= a;
			y /= a;
			z /= a;
			w /= a;
			return *this;
		};

		inline bool operator==(const float a) const
		{
			return (x == a) && (y == a) && (z == a) && (w == a);
		};

		inline bool operator==(const Liar::Vector4& rhs) const
		{
			return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
		};

		inline bool operator!=(const float a) const
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

		inline float operator[](size_t index) const
		{
			return (&x)[index];
		};

		inline float& operator[](size_t index)
		{
			return (&x)[index];
		};

		inline float Distance(float cx, float cy, float cz, float cw) const
		{
			float tmpx = x - cx;
			float tmpy = y - cy;
			float tmpz = z - cz;
			float tmpw = w - cw;
			return sqrtf(tmpx*tmpx + tmpy * tmpy + tmpz * tmpz + tmpw * tmpw);
		};

		inline float Distance(const Liar::Vector4& rhs) const
		{
			return Distance(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline float Length() const
		{
			return sqrtf(x*x + y * y + z * z + w * w);
		};

		inline float LengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		inline Vector4& Normalize()
		{
			float xxyyzzww = x * x + y * y + z * z + w * w;
			if (xxyyzzww)
			{
				float invLength = 1.0f / sqrtf(xxyyzzww);
				x *= invLength;
				y *= invLength;
				z *= invLength;
			}
			return *this;
		};

		inline void Normalize(Liar::Vector4& e)
		{
			float xxyyzzww = x * x + y * y + z * z + w * w;
			if (xxyyzzww > 0) {
				float len = 1.0f / sqrtf(len);
				e[0] = x * len;
				e[1] = y * len;
				e[2] = z * len;
				e[3] = w * len;
			}
		}

		inline float Dot(float cx, float cy, float cz, float cw) const
		{
			return (x*cx + y * cy + z * cz + w * cw);
		};

		inline float Dot(const Liar::Vector4& rhs) const
		{
			return Dot(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline bool Equal(float cx, float cy, float cz, float cw, float epsilon = Liar::MathUtils3D::ZERO_TO_LERANCE) const
		{
			return fabs(x - cx) < epsilon && fabs(y - cy) < epsilon && fabs(z - cz) < epsilon && fabs(w - cw) < epsilon;
		};

		inline bool Equal(const Liar::Vector4& rhs) const
		{
			return Equal(rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline Vector4& Scaling(float scaling)
		{
			x *= scaling;
			y *= scaling;
			z *= scaling;
			w *= scaling;
			return *this;
		};

		inline void Scaling(float scaling, Liar::Vector4& e)
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
		inline Vector4& RotateX(float rad)
		{
			float ax = x, ay = y, az = z, aw = w;
			float bx = sinf(rad), bw = cosf(rad);
			x = ax * bw + aw * bx;
			y = ay * bw + az * bx;
			z = az * bw - ay * bx;
			w = aw * bw - ax * bx;
			return *this;
		};

		inline void RotateX(float rad, Liar::Vector4& e)
		{
			float ax = x, ay = y, az = z, aw = w;
			float bx = sinf(rad), bw = cosf(rad);

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
		inline Vector4& RotateY(float rad)
		{
			float ax = x, ay = y, az = z, aw = w;
			float by = sinf(rad), bw = cosf(rad);
			x = ax * bw - az * by;
			y = ay * bw + aw * by;
			z = az * bw + ax * by;
			w = aw * bw - ay * by;
			return *this;
		};

		inline void RotateY(float rad, Liar::Vector4& e)
		{
			float ax = x, ay = y, az = z, aw = w;
			float by = sinf(rad), bw = cosf(rad);
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
		inline Vector4& RotateZ(float rad)
		{
			float ax = x, ay = y, az = z, aw = w;
			float bz = sinf(rad), bw = cosf(rad);
			x = ax * bw + ay * bz;
			y = ay * bw - ax * bz;
			z = az * bw + aw * bz;
			w = aw * bw - az * bz;
		};

		inline void RotateZ(float rad, Liar::Vector4& e)
		{
			float ax = x, ay = y, az = z, aw = w;
			float bz = sinf(rad), bw = cosf(rad);
			e[0] = ax * bw + ay * bz;
			e[1] = ay * bw - ax * bz;
			e[2] = az * bw + aw * bz;
			e[3] = aw * bw - az * bz;
		}
	};

	inline Vector4 operator*(const float a, const Vector4& vec) {
		return Vector4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return os;
	}
}

