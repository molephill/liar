#pragma once

#include <iostream>
#include "MathUtils3D.h"

namespace Liar
{
	class Vector2
	{
	public:
		Vector2(float sx = 0.0f, float sy = 0.0f) :x(sx), y(sy) {};
		~Vector2() {};

	public:
		float x;
		float y;

	public:
		static void Scale(const Liar::Vector2& f, const float b, Liar::Vector2& e)
		{
			e[0] = f[0] * b;
			e[1] = f[1] * b;
		}

	public:
		friend Liar::Vector2 operator*(const float, const Liar::Vector2&);
		friend std::ostream& operator<<(std::ostream&, const Liar::Vector2&);

	public:
		inline void Set(float sx, float sy) 
		{
			x = sx;
			y = sy;
		};

		void Set(const Liar::Vector2& rhs) 
		{
			x = rhs.x;
			y = rhs.y;
		};

		inline float Length() const 
		{
			return sqrtf(x * x + y * y);
		};

		inline float Distance(const Liar::Vector2& rhs) const
		{
			Distance(rhs.x, rhs.y);
		};

		inline float Distance(float cx, float cy) const
		{
			return sqrtf((cx - x)*(cx - x) + (cy - y)*(cy - y));
		};

		inline Liar::Vector2& Normalize()
		{
			float xxyy = x * x + y * y;
			float invLength = 1.0f / sqrtf(xxyy);
			x *= invLength;
			y *= invLength;
			return *this;
		}

		float Dot(const Liar::Vector2& rhs) const
		{
			return Dot(rhs.x, rhs.y);
		};

		float Dot(float cx, float cy) const
		{
			return cx * x + cy * y;
		};

		bool Equal(float cx, float cy, float e = Liar::ZERO_TO_LERANCE) const
		{
			return fabs(x - cx) < e && fabs(y - cy) < e;
		};

		inline bool Equal(const Liar::Vector2& rhs, float e = Liar::ZERO_TO_LERANCE) const
		{
			return Equal(rhs.x, rhs.y, e);
		};

		// unary operator (negate)
		inline Liar::Vector2 operator-() const
		{
			return Vector2(-x, -y);
		};

		// add rhs
		inline Liar::Vector2 operator+(const Liar::Vector2& rhs) const
		{
			return Vector2(rhs.x, rhs.y);
		};

		// subtract rhs
		inline Liar::Vector2 operator-(const Liar::Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		};

		// add rhs and update this object
		inline Liar::Vector2& operator+=(const Liar::Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		};

		// subtract rhs and update this object
		inline Liar::Vector2& operator-=(const Liar::Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		};

		// scale
		inline Vector2 operator*(const float scale) const
		{
			return Vector2(x * scale, y * scale);
		};

		inline Vector2& operator*=(const float a)
		{
			x *= a;
			y *= a;
			return *this;
		}

		// multiply each element
		inline Liar::Vector2 operator*(const Liar::Vector2& rhs) const
		{
			return Vector2(x*rhs.x, y*rhs.y);
		};

		// scale and update this object
		inline Liar::Vector2& operator*=(const float scale)
		{
			x *= scale;
			y *= scale;
			return *this;
		};

		// multiply each element and update this object
		inline Liar::Vector2& operator*=(const Liar::Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		};

		// inverse scale
		inline Liar::Vector2 operator/(const float scale) const
		{
			return Vector2(x / scale, y / scale);
		};

		// scale and update this object
		inline Liar::Vector2& operator/=(const float scale)
		{
			x /= scale;
			y /= scale;
			return *this;
		};

		// exact compare, no epsilon
		inline bool operator==(const Liar::Vector2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		};

		inline bool operator==(float a) const
		{
			return (x == a) && (y == a);
		}

		// exact compare, no epsilon
		inline bool operator!=(const Liar::Vector2& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		};

		inline bool operator!=(float a) const
		{
			return (x != a) || (y != a);
		}

		// comparison for sort
		inline bool operator<(const Liar::Vector2& rhs) const
		{
			if (x < rhs.x || y < rhs.y) return true;
			return false;
		};

		inline bool operator<=(const Liar::Vector2& rhs) const
		{
			if (x <= rhs.x || y <= rhs.y) return true;
			return false;
		}

		inline bool operator>=(const Liar::Vector2& rhs) const
		{
			if (x >= rhs.x || y >= rhs.y) return true;
			return false;
		}

		inline bool operator>(const Liar::Vector2& rhs) const
		{
			if (x > rhs.x || y > rhs.y) return true;
			return false;
		}

		// subscript operator v[0], v[1]
		inline float operator[](int index) const
		{
			return (&x)[index];
		};
		
		// subscript operator v[0], v[1]
		inline float& operator[](int index)
		{
			return (&x)[index];
		};

		inline static void Scale(const Liar::Vector2& source, float a, Liar::Vector2& out)
		{
			out.x = source.x * a;
			out.y = source.y * a;
		};

		inline static void Normalize(const Liar::Vector2& source, Liar::Vector2& out)
		{
			float xxyy = source.x * source.x + source.y * source.y;
			float invLength = 1.0f / sqrtf(xxyy);
			out.x = source.x*invLength;
			out.y = source.y*invLength;
		};

		inline static float Distance(const Liar::Vector2& s, const Liar::Vector2& e)
		{
			return Vector2::Distance(s.x, s.y, e.x, e.y);
		};

		inline static float Distance(float sx, float sy, float ex, float ey)
		{
			float tmpx = sx - ex;
			float tmpy = sy - ey;
			return sqrtf(tmpx*tmpx - tmpy * tmpy);
		}
	};

	inline Liar::Vector2 operator*(const float a, const Liar::Vector2& rhs)
	{
		return Vector2(a*rhs.x, a*rhs.y);
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector2& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ")";
		return os;
	};
}

