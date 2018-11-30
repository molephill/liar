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
			Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
		};
		Matrix4x4(const Liar::Matrix4x4& rhs)
		{
			Set(rhs);
		};
		~Matrix4x4() {};

	private:
		Liar::Number m[16];

	public:
		/**
		* 通过yaw pitch roll旋转创建旋转矩阵。
		* @param	yaw
		* @param	pitch
		* @param	roll
		* @param	result
		*/
		static void CreateRotationAxis(const Liar::Vector3& axisE, Liar::Number angle, Liar::Matrix4x4& resultE);

		/**
		* 根据平移计算输出矩阵
		* @param	trans  平移向量
		* @param	out 输出矩阵
		*/
		static void CreateTranslate(const Liar::Vector3& te, Liar::Matrix4x4& oe);

		/**
		* 根据缩放计算输出矩阵
		* @param	scale  缩放值
		* @param	out 输出矩阵
		*/
		static void CreateScaling(const Liar::Vector3& se, Liar::Matrix4x4& oe);

		/**
		* 计算两个矩阵的乘法
		* @param	left left矩阵
		* @param	right  right矩阵
		* @param	out  输出矩阵
		*/
		static void Multiply(const Liar::Matrix4x4& a, const Liar::Matrix4x4& tb, Liar::Matrix4x4& e);

		/**
		*  计算观察矩阵
		* @param	eye 视点位置
		* @param	center 视点目标
		* @param	up 向上向量
		* @param	out 输出矩阵
		*/
		static void CreateLookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Matrix4x4& oE);

		/**
		* 计算透视投影矩阵。
		* @param	fov  视角。
		* @param	aspect 横纵比。
		* @param	near 近裁面。
		* @param	far 远裁面。
		* @param	out 输出矩阵。
		*/
		static void CreatePerspective(Liar::Number fov, Liar::Number aspect, Liar::Number nearPlane, Liar::Number farPlane, Liar::Matrix4x4& oe);

		/**
		* 计算正交投影矩阵。
		* @param	left 视椎左边界。
		* @param	right 视椎右边界。
		* @param	bottom 视椎底边界。
		* @param	top 视椎顶边界。
		* @param	near 视椎近边界。
		* @param	far 视椎远边界。
		* @param	out 输出矩阵。
		*/
		static void CreateOrthoOffCenterRH(Liar::Number left, Liar::Number right, Liar::Number bottom, Liar::Number top, Liar::Number n, Liar::Number f, Liar::Matrix4x4& oe);

		static void Translation(const Liar::Vector3& ve, Liar::Matrix4x4& oe);

		// ====================== matrix4x4 ==================
		static void CreateFromQuaternion(const Liar::Quaternion&, Liar::Matrix4x4&);
		static void CreateAffineTransformation(const Liar::Vector3&, const Liar::Quaternion&, const Liar::Vector3&, Liar::Matrix4x4&);
		static void CreateRotationX(Liar::Number, Liar::Matrix4x4&);
		static void CreateRotationY(Liar::Number, Liar::Matrix4x4&);
		static void CreateRotationZ(Liar::Number, Liar::Matrix4x4&);

	public:
		friend Matrix4x4 operator-(const Matrix4x4& m);                     // unary operator (-)
		friend Matrix4x4 operator*(Liar::Number scalar, const Matrix4x4& m);       // pre-multiplication
		friend Vector3 operator*(const Vector3& vec, const Matrix4x4& m); // pre-multiplication
		friend Vector4 operator*(const Vector4& vec, const Matrix4x4& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);

	public:
		inline void Set(
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

		inline void Set(const Liar::Matrix4x4& rhs)
		{
			m[0] = rhs[0];  m[1] = rhs[1];  m[2] = rhs[2];  m[3] = rhs[3];
			m[4] = rhs[4];  m[5] = rhs[5];  m[6] = rhs[6];  m[7] = rhs[7];
			m[8] = rhs[8];  m[9] = rhs[9];  m[10] = rhs[10];  m[11] = rhs[11];
			m[12] = rhs[12];  m[13] = rhs[13];  m[14] = rhs[14];  m[15] = rhs[15];
		}

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

		inline bool EqualsOtherMatrix(const Liar::Matrix4x4& oe);

		/**
		* 分解矩阵为平移向量、旋转矩阵、缩放向量。
		* @param	translation 平移向量。
		* @param	rotationMatrix 旋转矩阵。
		* @param	scale 缩放向量。
		* @return 是否分解成功。
		*/
		bool DecomposeTransRotMatScale(Liar::Vector3& te, Liar::Matrix4x4& re, Liar::Vector3& se);

		/**
		* 分解旋转矩阵的旋转为YawPitchRoll欧拉角。
		* @param	out Liar::Number yaw
		* @param	out Liar::Number pitch
		* @param	out Liar::Number roll
		* @return
		*/
		void DecomposeYawPitchRoll(Liar::Vector3& yawPitchRollE);

		/**归一化矩阵 */
		void Normalize();

		/**计算矩阵的转置矩阵*/
		Matrix4x4& Transpose();

		void Invert(Liar::Matrix4x4& oe);

		inline Matrix4x4& Invert()
		{
			Invert(*this);
			return *this;
		};

		/**
		* 获取平移向量。
		* @param	out 平移向量。
		*/
		inline void GetTranslationVector(Liar::Vector3& te)
		{
			te[0] = m[12];
			te[1] = m[13];
			te[2] = m[14];
		};

		/**
		* 设置平移向量。
		* @param	translate 平移向量。
		*/
		inline void GetTranslationVector(const Liar::Vector3& ve)
		{
			m[12] = ve[0];
			m[13] = ve[1];
			m[14] = ve[2];
		};

		/**
		* 获取前向量。
		* @param	out 前向量。
		*/
		inline void GetForward(Liar::Vector3& te)
		{
			te[0] = -m[8];
			te[1] = -m[9];
			te[2] = -m[10];
		};

		/**
		* 设置前向量。
		* @param	forward 前向量。
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

