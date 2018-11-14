#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include <iostream>
#include <iomanip>

namespace Liar
{
	class Matrix4x4
	{
	public:
		Matrix4x4(
			Liar::Number m00 = 1.0f, Liar::Number m01 = 0.0f, Liar::Number m02 = 0.0f, Liar::Number m03 = 0.0f,
			Liar::Number m04 = 0.0f, Liar::Number m05 = 1.0f, Liar::Number m06 = 0.0f, Liar::Number m07 = 0.0f,
			Liar::Number m08 = 0.0f, Liar::Number m09 = 0.0f, Liar::Number m10 = 1.0f, Liar::Number m11 = 0.0f,
			Liar::Number m12 = 0.0f, Liar::Number m13 = 0.0f, Liar::Number m14 = 0.0f, Liar::Number m15 = 1.0f)
		{
			m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
			m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
			m[8] = m08;  m[9] = m09;  m[10] = m10;  m[11] = m11;
			m[12] = m12;  m[13] = m13;  m[14] = m14;  m[15] = m15;
		};
		~Matrix4x4() {};

	private:
		Liar::Number m[16];

	public:
		/**
		* ��X����ת
		* @param	rad  ��ת�Ƕ�
		* @param	out �������
		*/
		static void CreateRotationX(Liar::Number rad, Liar::Matrix4x4& oe)
		{
			Liar::Number s = sinf(rad), c = cosf(rad);
			oe[1] = oe[2] = oe[3] = oe[4] = oe[7] = oe[8] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
			oe[0] = oe[15] = 1;
			oe[5] = oe[10] = c;
			oe[6] = s;
			oe[9] = -s;
		};

		/**
		*
		* ��Y����ת
		* @param	rad  ��ת�Ƕ�
		* @param	out �������
		*/
		static void CreateRotationY(Liar::Number rad, Liar::Matrix4x4& oe)
		{
			Liar::Number s = sinf(rad), c = cosf(rad);
			oe[1] = oe[3] = oe[4] = oe[6] = oe[7] = oe[9] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
			oe[5] = oe[15] = 1;
			oe[0] = oe[10] = c;
			oe[2] = -s;
			oe[8] = s;
		};

		/**
		* ��Z����ת
		* @param	rad  ��ת�Ƕ�
		* @param	out �������
		*/
		static void CreateRotationZ(Liar::Number rad, Liar::Matrix4x4& oe)
		{
			Liar::Number s = sinf(rad), c = cosf(rad);
			oe[2] = oe[3] = oe[6] = oe[7] = oe[8] = oe[9] = oe[11] = oe[12] = oe[13] = oe[14] = 0;
			oe[10] = oe[15] = 1;
			oe[0] = oe[5] = c;
			oe[1] = s;
			oe[4] = -s;
		};

		/**
		* ͨ��yaw pitch roll��ת������ת����
		* @param	yaw
		* @param	pitch
		* @param	roll
		* @param	result
		*/
		static void CreateRotationAxis(const Liar::Vector3& axisE, Liar::Number angle, Liar::Matrix4x4& resultE)
		{
			Liar::Number x = axisE[0], y = axisE[1], z = axisE[2];
			Liar::Number cos = cosf(angle), sin = sinf(angle);
			Liar::Number xx = x * x;
			Liar::Number yy = y * y;
			Liar::Number zz = z * z;
			Liar::Number xy = x * y;
			Liar::Number xz = x * z;
			Liar::Number yz = y * z;

			resultE[3] = resultE[7] = resultE[11] = resultE[12] = resultE[13] = resultE[14] = 0.0f;
			resultE[15] = 1.0f;
			resultE[0] = xx + (cos * (1.0f - xx));
			resultE[1] = (xy - (cos * xy)) + (sin * z);
			resultE[2] = (xz - (cos * xz)) - (sin * y);
			resultE[4] = (xy - (cos * xy)) - (sin * z);
			resultE[5] = yy + (cos * (1.0f - yy));
			resultE[6] = (yz - (cos * yz)) + (sin * x);
			resultE[8] = (xz - (cos * xz)) + (sin * y);
			resultE[9] = (yz - (cos * yz)) - (sin * x);
			resultE[10] = zz + (cos * (1.0f - zz));
		};

		/**
		* ����ƽ�Ƽ����������
		* @param	trans  ƽ������
		* @param	out �������
		*/
		static void CreateTranslate(const Liar::Vector3& te, Liar::Matrix4x4& oe)
		{
			oe[4] = oe[8] = oe[1] = oe[9] = oe[2] = oe[6] = oe[3] = oe[7] = oe[11] = 0;
			oe[0] = oe[5] = oe[10] = oe[15] = 1;
			oe[12] = te[0];
			oe[13] = te[1];
			oe[14] = te[2];
		};

		/**
		* �������ż����������
		* @param	scale  ����ֵ
		* @param	out �������
		*/
		static void CreateScaling(const Liar::Vector3& se, Liar::Matrix4x4& oe)
		{
			oe[0] = se[0];
			oe[5] = se[1];
			oe[10] = se[2];
			oe[1] = oe[4] = oe[8] = oe[12] = oe[9] = oe[13] = oe[2] = oe[6] = oe[14] = oe[3] = oe[7] = oe[11] = 0;
			oe[15] = 1;
		};

		/**
		* ������������ĳ˷�
		* @param	left left����
		* @param	right  right����
		* @param	out  �������
		*/
		static void Multiply(const Liar::Matrix4x4& a, const Liar::Matrix4x4& tb, Liar::Matrix4x4& e)
		{
			int i = 0;
			Liar::Number ai0 = 0.0f, ai1 = 0.0f, ai2 = 0.0f, ai3 = 0.0f;

			const Liar::Matrix4x4* TEMPBPoint = nullptr;
			if (&tb == &e)
			{
				for (i = 0; i < 16; ++i) 
				{
					Liar::MathUtils3D::TEMPMatrix0[i] = e[i];
				}

				TEMPBPoint = &(Liar::MathUtils3D::TEMPMatrix0);
			}
			else
			{
				TEMPBPoint = &tb;
			}

			const Liar::Matrix4x4& b = *TEMPBPoint;

			for (i = 0; i < 4; i++) 
			{
				ai0 = a[i];
				ai1 = a[i + 4];
				ai2 = a[i + 8];
				ai3 = a[i + 12];
				e[i] = ai0 * b[0] + ai1 * b[1] + ai2 * b[2] + ai3 * b[3];
				e[i + 4] = ai0 * b[4] + ai1 * b[5] + ai2 * b[6] + ai3 * b[7];
				e[i + 8] = ai0 * b[8] + ai1 * b[9] + ai2 * b[10] + ai3 * b[11];
				e[i + 12] = ai0 * b[12] + ai1 * b[13] + ai2 * b[14] + ai3 * b[15];
			}
		};

		/**
		*  ����۲����
		* @param	eye �ӵ�λ��
		* @param	center �ӵ�Ŀ��
		* @param	up ��������
		* @param	out �������
		*/
		static void CreateLookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Matrix4x4& oE)
		{
			Liar::Vector3::Subtract(eye, target, Liar::MathUtils3D::TEMPVector30);
			Liar::Vector3& xaxis = Liar::MathUtils3D::TEMPVector30;
			Liar::Vector3& yaxis = Liar::MathUtils3D::TEMPVector31;
			Liar::Vector3& zaxis = Liar::MathUtils3D::TEMPVector32;
			Liar::Vector3::Normalize(zaxis, zaxis);
			Liar::Vector3::Cross(up, zaxis, xaxis);
			Liar::Vector3::Normalize(xaxis, xaxis);
			Liar::Vector3::Cross(zaxis, xaxis, yaxis);

			oE.Identity();
			oE[0] = xaxis.x;
			oE[4] = xaxis.y;
			oE[8] = xaxis.z;
			oE[1] = yaxis.x;
			oE[5] = yaxis.y;
			oE[9] = yaxis.z;
			oE[2] = zaxis.x;
			oE[6] = zaxis.y;
			oE[10] = zaxis.z;

			oE[12] = -Liar::Vector3::Dot(xaxis, eye);
			oE[13] = -Liar::Vector3::Dot(yaxis, eye);
			oE[14] = -Liar::Vector3::Dot(zaxis, eye);
		};

		/**
		* ����͸��ͶӰ����
		* @param	fov  �ӽǡ�
		* @param	aspect ���ݱȡ�
		* @param	near �����档
		* @param	far Զ���档
		* @param	out �������
		*/
		static void CreatePerspective(Liar::Number fov, Liar::Number aspect, Liar::Number nearPlane, Liar::Number farPlane, Liar::Matrix4x4& oe)
		{
			Liar::Number f = 1.0f / tanf(fov*0.5f);
			Liar::Number nf = 1.0f / (nearPlane - farPlane);
			oe[0] = f / aspect;
			oe[5] = f;
			oe[10] = (farPlane + nearPlane) * nf;
			oe[11] = -1.0f;
			oe[14] = (2.0f * f * nearPlane) * nf;
			oe[1] = oe[2] = oe[3] = oe[4] = oe[6] = oe[7] = oe[8] = oe[9] = oe[12] = oe[13] = oe[15] = 0.0f;
		};

		/**
		* ��������ͶӰ����
		* @param	left ��׵��߽硣
		* @param	right ��׵�ұ߽硣
		* @param	bottom ��׵�ױ߽硣
		* @param	top ��׵���߽硣
		* @param	near ��׵���߽硣
		* @param	far ��׵Զ�߽硣
		* @param	out �������
		*/
		static void CreateOrthoOffCenterRH(Liar::Number left, Liar::Number right, Liar::Number bottom, Liar::Number top, Liar::Number n, Liar::Number f, Liar::Matrix4x4& oe)
		{
			Liar::Number lr = 1.0f / (left - right);
			Liar::Number bt = 1.0f / (bottom - top);
			Liar::Number nf = 1.0f / (n - f);

			oe[1] = oe[2] = oe[3] = oe[4] = oe[6] = oe[7] = oe[8] = oe[9] = oe[11] = 0;
			oe[15] = 1;
			oe[0] = -2 * lr;
			oe[5] = -2 * bt;
			oe[10] = 2 * nf;
			oe[12] = (left + right) * lr;
			oe[13] = (top + bottom) * bt;
			oe[14] = (f + n) * nf;
		};

		static void Translation(const Liar::Vector3& ve, Liar::Matrix4x4& oe)
		{
			oe[0] = oe[5] = oe[10] = oe[15] = 1.0f;
			oe[12] = ve[0];
			oe[13] = ve[1];
			oe[14] = ve[2];
		}

	public:
		friend Matrix4x4 operator-(const Matrix4x4& m);                     // unary operator (-)
		friend Matrix4x4 operator*(Liar::Number scalar, const Matrix4x4& m);       // pre-multiplication
		friend Vector3 operator*(const Vector3& vec, const Matrix4x4& m); // pre-multiplication
		friend Vector4 operator*(const Vector4& vec, const Matrix4x4& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);

	public:
		inline void Set(Liar::Number m00, Liar::Number m01, Liar::Number m02, Liar::Number m03,
			Liar::Number m04, Liar::Number m05, Liar::Number m06, Liar::Number m07,
			Liar::Number m08, Liar::Number m09, Liar::Number m10, Liar::Number m11,
			Liar::Number m12, Liar::Number m13, Liar::Number m14, Liar::Number m15)
		{
			m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
			m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
			m[8] = m08;  m[9] = m09;  m[10] = m10;  m[11] = m11;
			m[12] = m12;  m[13] = m13;  m[14] = m14;  m[15] = m15;
		};

		inline void Identity()
		{
			m[0] = m[5] = m[10] = m[15] = 1.0f;
			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
		};

		inline Liar::Number operator[](int index) const
		{
			return m[index];
		};

		inline Liar::Number& operator[](int index)
		{
			return m[index];
		};

		inline void SetRow(size_t index, Liar::Number a, Liar::Number b, Liar::Number c, Liar::Number d)
		{
			m[index] = a;  
			m[index + 4] = b;  
			m[index + 8] = c;  
			m[index + 12] = d;
		};
		
		inline void SetRow(size_t index, const Liar::Vector4& rhs)
		{
			SetRow(index, rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline void SetColumn(size_t index, Liar::Number a, Liar::Number b, Liar::Number c, Liar::Number d)
		{
			m[index * 4] = a; 
			m[index * 4 + 1] = b; 
			m[index * 4 + 2] = c; 
			m[index * 4 + 3] = d;
		};

		inline void SetColumn(size_t index, const Liar::Vector4& rhs)
		{
			SetColumn(index, rhs.x, rhs.y, rhs.z, rhs.w);
		};

		inline const Liar::Number* Get() const
		{
			return m;
		};

		inline Matrix4x4 operator+(const Liar::Matrix4x4& rhs) const
		{
			return Matrix4x4(
				m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
				m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
				m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
				m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]
			);
		};

		inline Matrix4x4& operator+=(const Liar::Matrix4x4& rhs)
		{
			m[0] += rhs[0];   m[1] += rhs[1];   m[2] += rhs[2];   m[3] += rhs[3];
			m[4] += rhs[4];   m[5] += rhs[5];   m[6] += rhs[6];   m[7] += rhs[7];
			m[8] += rhs[8];   m[9] += rhs[9];   m[10] += rhs[10];  m[11] += rhs[11];
			m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
			return *this;
		};

		inline Matrix4x4 operator-(const Liar::Matrix4x4& rhs) const
		{
			return Matrix4x4(
				m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
				m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
				m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
				m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]
			);
		};

		inline Matrix4x4 operator-=(const Liar::Matrix4x4& rhs)
		{
			m[0] -= rhs[0];   m[1] -= rhs[1];   m[2] -= rhs[2];   m[3] -= rhs[3];
			m[4] -= rhs[4];   m[5] -= rhs[5];   m[6] -= rhs[6];   m[7] -= rhs[7];
			m[8] -= rhs[8];   m[9] -= rhs[9];   m[10] -= rhs[10];  m[11] -= rhs[11];
			m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
			return *this;
		};

		inline Vector4 operator*(const Liar::Vector4& rhs) const
		{
			return Vector4(
				m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12] * rhs.w,
				m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13] * rhs.w,
				m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14] * rhs.w,
				m[3] * rhs.x + m[7] * rhs.y + m[11] * rhs.z + m[15] * rhs.w);
		};

		inline Vector3 operator*(const Liar::Vector3& rhs) const
		{
			return Vector3(
				m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12],
				m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13],
				m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14]
			);
		};

		inline Matrix4x4 operator*(const Liar::Matrix4x4& n) const
		{
			return Matrix4x4(
				m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3], m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3], m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3], m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
				m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7], m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7], m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7], m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
				m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11], m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11], m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11], m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
				m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]
			);
		};

		inline Matrix4x4& operator*=(const Liar::Matrix4x4& n)
		{
			this->Set(m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3], m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3], m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3], m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
				m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7], m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7], m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7], m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
				m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11], m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11], m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11], m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
				m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]);
			return *this;
		};

		inline bool operator==(const Liar::Matrix4x4& n) const
		{
			return (
				m[0] == n[0]) && (m[1] == n[1]) && (m[2] == n[2]) && (m[3] == n[3]) &&
				(m[4] == n[4]) && (m[5] == n[5]) && (m[6] == n[6]) && (m[7] == n[7]) &&
				(m[8] == n[8]) && (m[9] == n[9]) && (m[10] == n[10]) && (m[11] == n[11]) &&
				(m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]
					);
		};

		inline bool operator!=(const Liar::Matrix4x4& n) const
		{
			return (
				m[0] != n[0]) || (m[1] != n[1]) || (m[2] != n[2]) || (m[3] != n[3]) ||
				(m[4] != n[4]) || (m[5] != n[5]) || (m[6] != n[6]) || (m[7] != n[7]) ||
				(m[8] != n[8]) || (m[9] != n[9]) || (m[10] != n[10]) || (m[11] != n[11]) ||
				(m[12] != n[12]) || (m[13] != n[13]) || (m[14] != n[14]) || (m[15] != n[15]
					);
		};

		inline Liar::Number GetElementByRowColumn(size_t row, size_t column) const
		{
			return m[row * 4 + column];
		};

		inline void SetElementByRowColumn(size_t row, size_t column, Liar::Number value)
		{
			m[row * 4 + column] = value;
		}

		inline bool EqualsOtherMatrix(const Liar::Matrix4x4& oe)
		{
			return (
				Liar::MathUtils3D::NearEqual(m[0], oe[0]) && 
				Liar::MathUtils3D::NearEqual(m[1], oe[1]) &&
				Liar::MathUtils3D::NearEqual(m[2], oe[2]) &&
				Liar::MathUtils3D::NearEqual(m[3], oe[3]) &&
				Liar::MathUtils3D::NearEqual(m[4], oe[4]) &&
				Liar::MathUtils3D::NearEqual(m[5], oe[5]) &&
				Liar::MathUtils3D::NearEqual(m[6], oe[6]) &&
				Liar::MathUtils3D::NearEqual(m[7], oe[7]) &&
				Liar::MathUtils3D::NearEqual(m[8], oe[8]) &&
				Liar::MathUtils3D::NearEqual(m[9], oe[9]) &&
				Liar::MathUtils3D::NearEqual(m[10], oe[10]) &&
				Liar::MathUtils3D::NearEqual(m[11], oe[11]) &&
				Liar::MathUtils3D::NearEqual(m[12], oe[12]) &&
				Liar::MathUtils3D::NearEqual(m[13], oe[13]) &&
				Liar::MathUtils3D::NearEqual(m[14], oe[14]) &&
				Liar::MathUtils3D::NearEqual(m[15], oe[15])
				);
		};

		/**
		* �ֽ����Ϊƽ����������ת��������������
		* @param	translation ƽ��������
		* @param	rotationMatrix ��ת����
		* @param	scale ����������
		* @return �Ƿ�ֽ�ɹ���
		*/
		bool DecomposeTransRotMatScale(Liar::Vector3& te, Liar::Matrix4x4& re, Liar::Vector3& se)
		{
			te[0] = m[12];
			te[1] = m[13];
			te[2] = m[14];

			Liar::Number m11 = m[0], m12 = m[1], m13 = m[2];
			Liar::Number m21 = m[4], m22 = m[5], m23 = m[6];
			Liar::Number m31 = m[8], m32 = m[9], m33 = m[10];

			Liar::Number sX = se[0] = sqrtf((m11 * m11) + (m12 * m12) + (m13 * m13));
			Liar::Number sY = se[1] = sqrtf((m21 * m21) + (m22 * m22) + (m23 * m23));
			Liar::Number sZ = se[2] = sqrtf((m31 * m31) + (m32 * m32) + (m33 * m33));

			if (MathUtils3D::IsZero(sX) || MathUtils3D::IsZero(sY) || MathUtils3D::IsZero(sZ)) 
			{
				re[1] = re[2] = re[3] = re[4] = re[6] = re[7] = re[8] = re[9] = re[11] = re[12] = re[13] = re[14] = 0;
				re[0] = re[5] = re[10] = re[15] = 1;
				return false;
			}

			Liar::Vector3& atE = Liar::MathUtils3D::TEMPVector30;
			atE[0] = m31 / sZ;
			atE[1] = m32 / sZ;
			atE[2] = m33 / sZ;

			Liar::Vector3& tempRightE = Liar::MathUtils3D::TEMPVector31;
			tempRightE[0] = m11 / sX;
			tempRightE[1] = m12 / sX;
			tempRightE[2] = m13 / sX;

			Liar::Vector3& up = Liar::MathUtils3D::TEMPVector32;
			Liar::Vector3::Cross(atE, tempRightE, up);

			Liar::Vector3& right = Liar::MathUtils3D::TEMPVector33;
			Liar::Vector3::Cross(up, atE, right);

			re[3] = re[7] = re[11] = re[12] = re[13] = re[14] = 0;
			re[15] = 1;
			re[0] = right.x;
			re[1] = right.y;
			re[2] = right.z;

			re[4] = up.x;
			re[5] = up.y;
			re[6] = up.z;

			re[8] = atE.x;
			re[9] = atE.y;
			re[10] = atE.z;

			// In case of reflexions//TODO:�Ƿ��ü���dot���ֵ��Ϊ���
			((re[0] * m11 + re[1] * m12 + re[2] * m13)/*Vector3.dot(right,Right)*/ < 0.0) && (se[0] = -sX);
			((re[4] * m21 + re[5] * m22 + re[6] * m23)/* Vector3.dot(up, Up)*/ < 0.0) && (se[1] = -sY);
			((re[8] * m31 + re[9] * m32 + re[10] * m33)/*Vector3.dot(at, Backward)*/ < 0.0) && (se[2] = -sZ);

			return true;
		};

		/**
		* �ֽ���ת�������תΪYawPitchRollŷ���ǡ�
		* @param	out Liar::Number yaw
		* @param	out Liar::Number pitch
		* @param	out Liar::Number roll
		* @return
		*/
		void DecomposeYawPitchRoll(Liar::Vector3& yawPitchRollE)
		{
			Liar::Number pitch = asinf(-m[9]);
			yawPitchRollE[1] = pitch;
			Liar::Number test = cosf(pitch);
			if (test > Liar::MathUtils3D::ZERO_TO_LERANCE) 
			{
				yawPitchRollE[2] = atan2f(m[1], m[5]);
				yawPitchRollE[0] = atan2f(m[8], m[10]);
			}
			else 
			{
				yawPitchRollE[2] = atan2f(-m[4], m[0]);
				yawPitchRollE[0] = 0.0;
			}
		};

		/**��һ������ */
		inline void Normalize()
		{
			Liar::Number c = m[0], d = m[1], e = m[2];
			Liar::Number g = sqrt(c * c + d * d + e * e);
			if (g)
			{
				if (g == 1) return;
			}
			else
			{
				m[0] = m[1] = m[2] = 0.0f;
				return;
			}
			g = 1.0f / g;
			m[0] = c * g;
			m[1] = d * g;
			m[2] = e * g;
		};

		/**��������ת�þ���*/
		inline Matrix4x4& Transpose()
		{
			Liar::Number t = m[1];
			m[1] = m[4];
			m[4] = t;
			t = m[2];
			m[2] = m[8];
			m[8] = t;
			t = m[3];
			m[3] = m[12];
			m[12] = t;
			t = m[6];
			m[6] = m[9];
			m[9] = t;
			t = m[7];
			m[7] = m[13];
			m[13] = t;
			t = m[11];
			m[11] = m[14];
			m[14] = t;

			return *this;
		};

		inline void Invert(Liar::Matrix4x4& oe)
		{
			Liar::Number a00 = m[0], a01 = m[1], a02 = m[2], a03 = m[3];
			Liar::Number a10 = m[4], a11 = m[5], a12 = m[6], a13 = m[7];
			Liar::Number a20 = m[8], a21 = m[9], a22 = m[10], a23 = m[11];
			Liar::Number a30 = m[12], a31 = m[13], a32 = m[14], a33 = m[15];

			Liar::Number b00 = a00 * a11 - a01 * a10;
			Liar::Number b01 = a00 * a12 - a02 * a10;
			Liar::Number b02 = a00 * a13 - a03 * a10;
			Liar::Number b03 = a01 * a12 - a02 * a11;
			Liar::Number b04 = a01 * a13 - a03 * a11;
			Liar::Number b05 = a02 * a13 - a03 * a12;
			Liar::Number b06 = a20 * a31 - a21 * a30;
			Liar::Number b07 = a20 * a32 - a22 * a30;
			Liar::Number b08 = a20 * a33 - a23 * a30;
			Liar::Number b09 = a21 * a32 - a22 * a31;
			Liar::Number b10 = a21 * a33 - a23 * a31;
			Liar::Number b11 = a22 * a33 - a23 * a32;

			Liar::Number det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
			if (abs(det) == 0)
			{
				return;
			}
			det = 1.0f / det;

			oe[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
			oe[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
			oe[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
			oe[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
			oe[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
			oe[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
			oe[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
			oe[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
			oe[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
			oe[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
			oe[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
			oe[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
			oe[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
			oe[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
			oe[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
			oe[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
		}

		inline Matrix4x4& Invert()
		{
			Invert(*this);
			return *this;
		};

		/**
		* ��ȡƽ��������
		* @param	out ƽ��������
		*/
		inline void GetTranslationVector(Liar::Vector3& te)
		{
			te[0] = m[12];
			te[1] = m[13];
			te[2] = m[14];
		};

		/**
		* ����ƽ��������
		* @param	translate ƽ��������
		*/
		inline void GetTranslationVector(const Liar::Vector3& ve)
		{
			m[12] = ve[0];
			m[13] = ve[1];
			m[14] = ve[2];
		};

		/**
		* ��ȡǰ������
		* @param	out ǰ������
		*/
		inline void GetForward(Liar::Vector3& te)
		{
			te[0] = -m[8];
			te[1] = -m[9];
			te[2] = -m[10];
		};

		/**
		* ����ǰ������
		* @param	forward ǰ������
		*/
		inline void SetForward(const Liar::Vector3& ve)
		{
			m[8] = -ve[0];
			m[9] = -ve[1];
			m[10] = -ve[2];
		}

	};

	inline Matrix4x4 operator-(const Matrix4x4& rhs)
	{
		return Matrix4x4(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8], -rhs[9], -rhs[10], -rhs[11], -rhs[12], -rhs[13], -rhs[14], -rhs[15]);
	}

	inline Matrix4x4 operator*(Liar::Number s, const Matrix4x4& rhs)
	{
		return Matrix4x4(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8], s*rhs[9], s*rhs[10], s*rhs[11], s*rhs[12], s*rhs[13], s*rhs[14], s*rhs[15]);
	}

	inline Vector4 operator*(const Vector4& v, const Matrix4x4& m)
	{
		return Vector4(v.x*m[0] + v.y*m[1] + v.z*m[2] + v.w*m[3], v.x*m[4] + v.y*m[5] + v.z*m[6] + v.w*m[7], v.x*m[8] + v.y*m[9] + v.z*m[10] + v.w*m[11], v.x*m[12] + v.y*m[13] + v.z*m[14] + v.w*m[15]);
	}

	inline Vector3 operator*(const Vector3& v, const Matrix4x4& m)
	{
		return Vector3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[4] + v.y*m[5] + v.z*m[6], v.x*m[8] + v.y*m[9] + v.z*m[10]);
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[8] << " " << std::setw(10) << m[12] << "]\n"
			<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[9] << " " << std::setw(10) << m[13] << "]\n"
			<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[6] << " " << std::setw(10) << m[10] << " " << std::setw(10) << m[14] << "]\n"
			<< "[" << std::setw(10) << m[3] << " " << std::setw(10) << m[7] << " " << std::setw(10) << m[11] << " " << std::setw(10) << m[15] << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	};
}

