#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <iostream>
#include <iomanip>

namespace Liar
{
	class Matrix3x3
	{
	public:
		Matrix3x3(
			Liar::Number m0 = 1.0f, Liar::Number m1 = 0.0f, Liar::Number m2 = 0.0f,
			Liar::Number m3 = 0.0f, Liar::Number m4 = 0.0f, Liar::Number m5 = 0.0f,
			Liar::Number m6 = 0.0f, Liar::Number m7 = 0.0f, Liar::Number m8 = 1.0f)
		{
			Set(m0, m1, m2, m3, m4, m5, m6, m7, m8);
		};
		~Matrix3x3() {};

	private:
		Liar::Number m[9];

	public:
		friend Matrix3x3 operator-(const Matrix3x3& m);                     // unary operator (-)
		friend Matrix3x3 operator*(Liar::Number scalar, const Matrix3x3& m);       // pre-multiplication
		friend Vector3 operator*(const Vector3& vec, const Matrix3x3& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Matrix3x3& m);

	public:
		static void CreateFromTranslation(const Liar::Vector2& g, Liar::Matrix3x3& out);
		static void CreateFromRotation(Liar::Number rad, Liar::Matrix3x3& e);
		static void CreateFromScaling(const Liar::Vector2& g, Liar::Matrix3x3& e);
		static void Multiply(const Liar::Matrix3x3& f, const Liar::Matrix3x3& g, Liar::Matrix3x3& e);
		static void Invert(const Liar::Matrix3x3& m, Liar::Matrix3x3& e);
		static void Transpose(const Liar::Matrix3x3& f, Liar::Matrix3x3& e);
		// ====================== matrix3x3 ==================
		static void CreateFromMatrix4x4(const Liar::Matrix4x4&, Liar::Matrix3x3&);
		static void LookAt(const Liar::Vector3&, const Liar::Vector3&, const Liar::Vector3&, Liar::Matrix3x3&);

	public:
		inline Liar::Number operator[](int index) const
		{
			return m[index];
		};

		inline Liar::Number& operator[](int index)
		{
			return m[index];
		};

		inline void Set(
			Liar::Number m0 = 1.0f, Liar::Number m1 = 0.0f, Liar::Number m2 = 0.0f,
			Liar::Number m3 = 0.0f, Liar::Number m4 = 0.0f, Liar::Number m5 = 0.0f,
			Liar::Number m6 = 0.0f, Liar::Number m7 = 0.0f, Liar::Number m8 = 1.0f)
		{
			m[0] = m0;  m[1] = m1;  m[2] = m2;
			m[3] = m3;  m[4] = m4;  m[5] = m5;
			m[6] = m6;  m[7] = m7;  m[8] = m8;
		};

		inline void SetRow(size_t index, Liar::Number a, Liar::Number b, Liar::Number c)
		{
			m[index] = a;
			m[index + 3] = b;
			m[index + 6] = c;
		};

		inline void SetRow(size_t index, const Liar::Number row[3])
		{
			SetRow(index, row[0], row[1], row[2]);
		};

		inline void SetRow(size_t index, const Liar::Vector3& rhs)
		{
			SetRow(index, rhs.x, rhs.y, rhs.z);
		};

		inline void SetColumn(size_t index, Liar::Number a, Liar::Number b, Liar::Number c)
		{
			m[index * 3] = a;
			m[index * 3 + 1] = b;
			m[index * 3 + 2] = c;
		};

		inline void SetColumn(size_t index, const Liar::Number col[3])
		{
			SetColumn(index, col[0], col[1], col[2]);
		};

		inline void SetColumn(size_t index, const Liar::Vector3& rhs)
		{
			SetColumn(index, rhs.x, rhs.y, rhs.z);
		};

		inline const Liar::Number* Get() const
		{
			return m;
		};

		inline Matrix3x3& Identity()
		{
			m[0] = m[4] = m[8] = 1.0f;
			m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
			return *this;
		};

		inline Matrix3x3 operator+(const Liar::Matrix3x3& rhs) const
		{
			return Matrix3x3(
				m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
				m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
				m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]
			);
		}

		inline Matrix3x3& operator+=(const Liar::Matrix3x3& rhs)
		{
			m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
			m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
			m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
			return *this;
		};

		inline Matrix3x3 operator-(const Matrix3x3& rhs) const
		{
			return Matrix3x3(
				m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
				m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
				m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]
			);
		};

		inline Matrix3x3& operator-=(const Liar::Matrix3x3& rhs)
		{
			m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
			m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
			m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
			return *this;
		};

		inline Vector3 operator*(const Liar::Vector3& rhs) const
		{
			return Vector3(
				m[0] * rhs.x + m[3] * rhs.y + m[6] * rhs.z,
				m[1] * rhs.x + m[4] * rhs.y + m[7] * rhs.z,
				m[2] * rhs.x + m[5] * rhs.y + m[8] * rhs.z
			);
		};

		inline Matrix3x3 operator*(const Liar::Matrix3x3& rhs) const
		{
			return Matrix3x3(
				m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
				m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
				m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]
			);
		};

		inline Matrix3x3& operator*=(const Liar::Matrix3x3& rhs)
		{
			this->Set(
				m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
				m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
				m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]
			);
			return *this;
		};

		inline bool operator==(const Liar::Matrix3x3& rhs) const
		{
			return
				(m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
				(m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
				(m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
		};

		inline bool operator!=(const Liar::Matrix3x3& rhs) const
		{
			return
				(m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
				(m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
				(m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
		};

		inline Liar::Number Determinant() const
		{
			Liar::Number a00 = m[0], a01 = m[1], a02 = m[2];
			Liar::Number a10 = m[3], a11 = m[4], a12 = m[5];
			Liar::Number a20 = m[6], a21 = m[7], a22 = m[8];
			return a00 * (a22 * a11 - a12 * a21) + a01 * (-a22 * a10 + a12 * a20) + a02 * (a21 * a10 - a11 * a20);
		};

		inline void Translate(const Liar::Vector2& g, Liar::Matrix3x3 & e)
		{
			Liar::Number a00 = m[0], a01 = m[1], a02 = m[2];
			Liar::Number a10 = m[3], a11 = m[4], a12 = m[5];
			Liar::Number a20 = m[6], a21 = m[7], a22 = m[8];

			Liar::Number x = g.x, y = g.y;

			e[0] = a00;
			e[1] = a01;
			e[2] = a02;

			e[3] = a10;
			e[4] = a11;
			e[5] = a12;

			e[6] = x * a00 + y * a10 + a20;
			e[7] = x * a01 + y * a11 + a21;
			e[8] = x * a02 + y * a12 + a22;
		};

		inline void Rotate(Liar::Number rad, Liar::Matrix3x3& e)
		{
			Liar::Number a00 = m[0], a01 = m[1], a02 = m[2];
			Liar::Number a10 = m[3], a11 = m[4], a12 = m[5];
			Liar::Number a20 = m[6], a21 = m[7], a22 = m[8];

			Liar::Number s = sinf(rad);
			Liar::Number c = cosf(rad);

			e[0] = c * a00 + s * a10;
			e[1] = c * a01 + s * a11;
			e[2] = c * a02 + s * a12;

			e[3] = c * a10 - s * a00;
			e[4] = c * a11 - s * a01;
			e[5] = c * a12 - s * a02;

			e[6] = a20;
			e[7] = a21;
			e[8] = a22;
		};

		inline void Scale(const Liar::Vector2& g, Liar::Matrix3x3& e)
		{
			Liar::Number x = g.x, y = g.y;

			e[0] = x * m[0];
			e[1] = x * m[1];
			e[2] = x * m[2];

			e[3] = y * m[3];
			e[4] = y * m[4];
			e[5] = y * m[5];

			e[6] = m[6];
			e[7] = m[7];
			e[8] = m[8];
		};

		inline Matrix3x3& Invert()
		{
			Liar::Number a00 = m[0], a01 = m[1], a02 = m[2];
			Liar::Number a10 = m[3], a11 = m[4], a12 = m[5];
			Liar::Number a20 = m[6], a21 = m[7], a22 = m[8];

			Liar::Number b01 = a22 * a11 - a12 * a21;
			Liar::Number b11 = -a22 * a10 + a12 * a20;
			Liar::Number b21 = a21 * a10 - a11 * a20;

			Liar::Number det = a00 * b01 + a01 * b11 + a02 * b21;

			if (det)
			{
				det = 1.0f / det;
				m[0] = b01 * det;
				m[1] = (-a22 * a01 + a02 * a21) * det;
				m[2] = (a12 * a01 - a02 * a11) * det;
				m[3] = b11 * det;
				m[4] = (a22 * a00 - a02 * a20) * det;
				m[5] = (-a12 * a00 + a02 * a10) * det;
				m[6] = b21 * det;
				m[7] = (-a21 * a00 + a01 * a20) * det;
				m[8] = (a11 * a00 - a01 * a10) * det;
			}

			return *this;
		}

		inline Matrix3x3& Transpose()
		{
			Liar::Number a01 = m[1], a02 = m[2], a12 = m[5];
			m[1] = m[3];
			m[2] = m[6];
			m[3] = a01;
			m[5] = m[7];
			m[6] = a02;
			m[7] = a12;
			return *this;
		};

	};

	inline Matrix3x3 operator-(const Matrix3x3& rhs)
	{
		return Matrix3x3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8]);
	}

	inline Matrix3x3 operator*(Liar::Number s, const Matrix3x3& rhs)
	{
		return Matrix3x3(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8]);
	}

	inline Vector3 operator*(const Vector3& v, const Matrix3x3& m)
	{
		return Vector3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[3] + v.y*m[4] + v.z*m[5], v.x*m[6] + v.y*m[7] + v.z*m[8]);
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix3x3& m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[3] << " " << std::setw(10) << m[6] << "]\n"
			<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[7] << "]\n"
			<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[8] << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	}
}

