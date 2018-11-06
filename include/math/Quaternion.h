#pragma once

#include "Vector4.h"
#include "Matrix3x3.h"

namespace Liar
{
	class Quaternion:public Vector4
	{
	public:
		Quaternion(float cx = 0.0f, float cy = 0.0f, float cz = 0.0f, float cw = 1.0f) :Vector4(cx, cy, cz, cw) {};
		~Quaternion() {};

	public:
		/**
		*  从欧拉角生成四元数（顺序为Yaw、Pitch、Roll）
		* @param	yaw yaw值
		* @param	pitch pitch值
		* @param	roll roll值
		* @param	out 输出四元数
		*/
		static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Liar::Quaternion& oe)
		{
			float halfRoll = roll * 0.5;
			float halfPitch = pitch * 0.5;
			float halfYaw = yaw * 0.5;

			float sinRoll = sinf(halfRoll);
			float cosRoll = cosf(halfRoll);
			float sinPitch = sinf(halfPitch);
			float cosPitch = cosf(halfPitch);
			float sinYaw = sinf(halfYaw);
			float cosYaw = cosf(halfYaw);

			oe[0] = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
			oe[1] = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
			oe[2] = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
			oe[3] = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
		};

		/**
		* 计算两个四元数相乘
		* @param	left left四元数
		* @param	right  right四元数
		* @param	out 输出四元数
		*/
		static void Multiply(const Liar::Quaternion& le, const Liar::Quaternion& re, Liar::Quaternion & oe)
		{
			float lx = le[0], ly = le[1], lz = le[2], lw = le[3];
			float rx = re[0], ry = re[1], rz = re[2], rw = re[3];

			float a = (ly * rz - lz * ry);
			float b = (lz * rx - lx * rz);
			float c = (lx * ry - ly * rx);
			float d = (lx * rx + ly * ry + lz * rz);

			oe[0] = (lx * rw + rx * lw) + a;
			oe[1] = (ly * rw + ry * lw) + b;
			oe[2] = (lz * rw + rz * lw) + c;
			oe[3] = lw * rw - d;
		};

		static float ArcTanAngle(float x, float y)
		{
			if (x == 0) {
				if (y == 1)
					return Liar::MathUtils3D::PI / 2;
				return -Liar::MathUtils3D::PI / 2;
			}
			if (x > 0)
				return atanf(y / x);
			if (x < 0) {
				if (y > 0)
					return atanf(y / x) + Liar::MathUtils3D::PI;
				return atanf(y / x) - Liar::MathUtils3D::PI;
			}
			return 0;
		}

		static void AngleTo(const Liar::Vector3& from, const Liar::Vector3& location, Liar::Vector3& angle)
		{
			Liar::Vector3 TEMPVector30;
			Vector3::Subtract(location, from, TEMPVector30);
			Vector3::Normalize(TEMPVector30, TEMPVector30);
			angle[0] = asinf(TEMPVector30.y);
			angle[1] = Quaternion::ArcTanAngle(-TEMPVector30.z, -TEMPVector30.x);
		}

		/**
		* 从指定的轴和角度计算四元数
		* @param	axis  轴
		* @param	rad  角度
		* @param	out  输出四元数
		*/
		static void CreateFromAxisAngle(const Liar::Vector3& axis, float rad, Liar::Quaternion& e)
		{
			float halfRad = rad * 0.5f;
			float s = sinf(rad);
			e[0] = s * axis[0];
			e[1] = s * axis[1];
			e[2] = s * axis[2];
			e[3] = cosf(rad);
		};

		/**
		* 根据3x3矩阵计算四元数
		* @param	sou 源矩阵
		* @param	out 输出四元数
		*/
		static void CreateFromMatrix3x3(const Liar::Matrix3x3& f, Liar::Quaternion& e)
		{
			float fTrace = f[0] + f[4] + f[8];
			float fRoot = 0.0f;
			if (fTrace > 0.0) {
				// |w| > 1/2, may as well choose w > 1/2
				fRoot = sqrtf(fTrace + 1.0);  // 2w
				e[3] = 0.5 * fRoot;
				fRoot = 0.5 / fRoot;  // 1/(4w)
				e[0] = (f[5] - f[7]) * fRoot;
				e[1] = (f[6] - f[2]) * fRoot;
				e[2] = (f[1] - f[3]) * fRoot;
			}
			else 
			{
				// |w| <= 1/2                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
				int i = 0.0f;
				if (f[4] > f[0])
				{
					i = 1;
				}
				if (f[8] > f[i * 3 + i])
				{
					i = 2;
				}
				int j = (i + 1) % 3;
				int k = (i + 2) % 3;

				fRoot = sqrtf(f[i * 3 + i] - f[j * 3 + j] - f[k * 3 + k] + 1.0);
				e[i] = 0.5 * fRoot;
				fRoot = 0.5 / fRoot;
				e[3] = (f[j * 3 + k] - f[k * 3 + j]) * fRoot;
				e[j] = (f[j * 3 + i] + f[i * 3 + j]) * fRoot;
				e[k] = (f[k * 3 + i] + f[i * 3 + k]) * fRoot;
			}
		};

		/**
		*  从旋转矩阵计算四元数
		* @param	mat 旋转矩阵
		* @param	out  输出四元数
		*/
		static void CreateFromMatrix4x4(const Liar::Matrix4x4& me, Liar::Quaternion& oe)
		{
			float sqrt = 0.0f, half = 0.0f;
			float scale = me[0] + me[5] + me[10];
			if (scale > 0.0f)
			{
				sqrt = sqrtf(scale + 1.0);
				oe[3] = sqrt * 0.5;
				sqrt = 0.5 / sqrt;

				oe[0] = (me[6] - me[9]) * sqrt;
				oe[1] = (me[8] - me[2]) * sqrt;
				oe[2] = (me[1] - me[4]) * sqrt;
			}
			else if ((me[0] >= me[5]) && (me[0] >= me[10]))
			{
				sqrt = sqrtf(1.0 + me[0] - me[5] - me[10]);
				half = 0.5 / sqrt;

				oe[0] = 0.5 * sqrt;
				oe[1] = (me[1] + me[4]) * half;
				oe[2] = (me[2] + me[8]) * half;
				oe[3] = (me[6] - me[9]) * half;
			}
			else if (me[5] > me[10])
			{
				sqrt = sqrtf(1.0 + me[5] - me[0] - me[10]);
				half = 0.5 / sqrt;

				oe[0] = (me[4] + me[1]) * half;
				oe[1] = 0.5 * sqrt;
				oe[2] = (me[9] + me[6]) * half;
				oe[3] = (me[8] - me[2]) * half;
			}
			else
			{
				sqrt = sqrtf(1.0 + me[10] - me[0] - me[5]);
				half = 0.5 / sqrt;

				oe[0] = (me[8] + me[2]) * half;
				oe[1] = (me[9] + me[6]) * half;
				oe[2] = 0.5 * sqrt;
				oe[3] = (me[1] - me[4]) * half;
			}
		};

		/**
		* 球面插值
		* @param	left left四元数
		* @param	right  right四元数
		* @param	a 插值比例
		* @param	out 输出四元数
		* @return
		*/
		static void Slert(const Liar::Quaternion& a, const Liar::Quaternion& b, float t, Liar::Quaternion& oe)
		{
			float ax = a[0], ay = a[1], az = a[2], aw = a[3];
			float bx = b[0], by = a[1], bz = a[2], bw = b[3];

			float omega = 0.0f, cosom = 0.0f, sinom = 0.0f, scale0 = 0.0f, scale1 = 0.0f;
			// calc cosine 
			cosom = ax * bx + ay * by + az * bz + aw * bw;
			// adjust signs (if necessary) 
			if (cosom < 0.0) 
			{
				cosom = -cosom;
				bx = -bx;
				by = -by;
				bz = -bz;
				bw = -bw;
			}
			// calculate coefficients 
			if ((1.0 - cosom) > 0.000001) 
			{
				// standard case (slerp) 
				omega = acosf(cosom);
				sinom = sinf(omega);
				scale0 = sinf((1.0 - t) * omega) / sinom;
				scale1 = sinf(t * omega) / sinom;
			}
			else 
			{
				// "from" and "to" quaternions are very close  
				//  ... so we can do a linear interpolation 
				scale0 = 1.0 - t;
				scale1 = t;
			}
			// calculate final values 
			oe[0] = scale0 * ax + scale1 * bx;
			oe[1] = scale0 * ay + scale1 * by;
			oe[2] = scale0 * az + scale1 * bz;
			oe[3] = scale0 * aw + scale1 * bw;
		};

		/**
		* 计算两个四元数的线性插值
		* @param	left left四元数
		* @param	right right四元数b
		* @param	t 插值比例
		* @param	out 输出四元数
		*/
		static void Lerp(const Liar::Quaternion& f, const Liar::Quaternion& g, float t, Liar::Quaternion& e)
		{
			float ax = f[0], ay = f[1], az = f[2], aw = f[3];
			e[0] = ax + t * (g[0] - ax);
			e[1] = ay + t * (g[1] - ay);
			e[2] = az + t * (g[2] - az);
			e[3] = aw + t * (g[3] - aw);
		};

		/**
		* 计算两个四元数的和
		* @param	left  left四元数
		* @param	right right 四元数
		* @param	out 输出四元数
		*/
		static void Add(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Quaternion& e)
		{
			e[0] = f[0] + g[0];
			e[1] = f[1] + g[1];
			e[2] = f[2] + g[2];
			e[3] = f[3] + g[3];
		};

		/**
		* 计算两个四元数的点积
		* @param	left left四元数
		* @param	right right四元数
		* @return  点积
		*/
		static float Dot(const Liar::Quaternion& f, const Liar::Quaternion& g)
		{
			return f[0] * g[0] + f[1] * g[1] + f[2] * g[2] + f[3] * g[3];
		};

		/**
		* 通过一个3x3矩阵创建一个四元数
		* @param	matrix3x3  3x3矩阵
		* @param	out        四元数
		*/
		static void RotationMatrix(const Liar::Matrix3x3& me, Liar::Quaternion& oe)
		{
			float m11 = me[0];
			float m12 = me[1];
			float m13 = me[2];
			float m21 = me[3];
			float m22 = me[4];
			float m23 = me[5];
			float m31 = me[6];
			float m32 = me[7];
			float m33 = me[8];

			float sqrt = 0, half = 0;
			float scale = m11 + m22 + m33;

			if (scale > 0) 
			{
				sqrt = sqrtf(scale + 1);
				oe[3] = sqrt * 0.5;
				sqrt = 0.5 / sqrt;

				oe[0] = (m23 - m32) * sqrt;
				oe[1] = (m31 - m13) * sqrt;
				oe[2] = (m12 - m21) * sqrt;
			}
			else if ((m11 >= m22) && (m11 >= m33)) 
			{
				sqrt = sqrtf(1 + m11 - m22 - m33);
				half = 0.5 / sqrt;

				oe[0] = 0.5 * sqrt;
				oe[1] = (m12 + m21) * half;
				oe[2] = (m13 + m31) * half;
				oe[3] = (m23 - m32) * half;
			}
			else if (m22 > m33) 
			{
				sqrt = sqrtf(1 + m22 - m11 - m33);
				half = 0.5 / sqrt;

				oe[0] = (m21 + m12) * half;
				oe[1] = 0.5 * sqrt;
				oe[2] = (m32 + m23) * half;
				oe[3] = (m31 - m13) * half;
			}
			else 
			{
				sqrt = sqrtf(1 + m33 - m11 - m22);
				half = 0.5 / sqrt;

				oe[0] = (m31 + m13) * half;
				oe[1] = (m32 + m23) * half;
				oe[2] = 0.5 * sqrt;
				oe[3] = (m12 - m21) * half;
			}
		}

		/**
		* 计算观察四元数
		* @param	eye    观察者位置
		* @param	target 目标位置
		* @param	up     上向量
		* @param	out    输出四元数
		*/
		static void LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Quaternion& out)
		{
			Matrix3x3::LookAt(eye, target, up, Liar::MathUtils3D::TEMPMatrix3x3);
			Quaternion::RotationMatrix(Liar::MathUtils3D::TEMPMatrix3x3, out);
		}

		/**
		* 计算旋转观察四元数
		* @param	forward 方向
		* @param	up     上向量
		* @param	out    输出四元数
		*/
		static void RotationLookAt(const Liar::Vector3& forward, const Liar::Vector3& up, Liar::Quaternion& out)
		{
			LookAt(Liar::MathUtils3D::ZERO, forward, up, out);
		};

		/**
		* 计算四元数的逆四元数。
		* @param	value 四元数。
		* @param	out 逆四元数。
		*/
		static void Invert(const Liar::Quaternion& vE, Liar::Quaternion& oE)
		{
			float lengthSq = vE.LengthSquared();
			if (lengthSq)
			{
				lengthSq = 1.0f / lengthSq;

				oE[0] = -vE[0] * lengthSq;
				oE[1] = -vE[1] * lengthSq;
				oE[2] = -vE[2] * lengthSq;
				oE[3] = vE[3] * lengthSq;
			}
		}

	public:
		/**
		* 分解四元数到欧拉角（顺序为Yaw、Pitch、Roll），参考自http://xboxforums.create.msdn.com/forums/p/4574/23988.aspx#23988,问题绕X轴翻转超过±90度时有，会产生瞬间反转
		* @param	quaternion 源四元数
		* @param	out 欧拉角值
		*/
		inline void GetYawPitchRoll(Liar::Vector3& oe)
		{
			Vector3::TransformQuat(Liar::MathUtils3D::ForwardRH, *this, Liar::MathUtils3D::TEMPVector31);
			Vector3::TransformQuat(Liar::MathUtils3D::Up, *this, Liar::MathUtils3D::TEMPVector32);
			Quaternion::AngleTo(Liar::MathUtils3D::ZERO, Liar::MathUtils3D::TEMPVector31, Liar::MathUtils3D::TEMPVector33);

			Liar::Vector3& upe = Liar::MathUtils3D::TEMPVector32;
			Liar::Vector3& anglee = Liar::MathUtils3D::TEMPVector33;
			if (anglee[0] == Liar::MathUtils3D::PI / 2) {
				anglee[1] = Quaternion::ArcTanAngle(upe[2], upe[0]);
				anglee[2] = 0;
			}
			else if (anglee[0] == -Liar::MathUtils3D::PI / 2) {
				anglee[1] = Quaternion::ArcTanAngle(-upe[2], -upe[0]);
				anglee[2] = 0;
			}
			else {
				Matrix4x4::CreateRotationY(-anglee[1], Liar::MathUtils3D::TEMPMatrix0);
				Matrix4x4::CreateRotationX(-anglee[0], Liar::MathUtils3D::TEMPMatrix1);

				Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector32);
				Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix1, Liar::MathUtils3D::TEMPVector32);
				anglee[2] = Quaternion::ArcTanAngle(upe[1], -upe[0]);
			}

			// Special cases.
			if (anglee[1] <= -Liar::MathUtils3D::PI)
				anglee[1] = Liar::MathUtils3D::PI;
			if (anglee[2] <= -Liar::MathUtils3D::PI)
				anglee[2] = Liar::MathUtils3D::PI;

			if (anglee[1] >= Liar::MathUtils3D::PI && anglee[2] >= Liar::MathUtils3D::PI)
			{
				anglee[1] = 0;
				anglee[2] = 0;
				anglee[0] = Liar::MathUtils3D::PI - anglee[0];
			}

			oe[0] = anglee[1];
			oe[1] = anglee[0];
			oe[2] = anglee[2];
		};

		inline Quaternion& Invert()
		{
			float a0 = x, a1 = y, a2 = z, a3 = w;
			float dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
			float invDot = dot ? 1.0f / dot : 0.0f;
			x = -a0 * invDot;
			y = -a1 * invDot;
			z = -a2 * invDot;
			w = a3 * invDot;
			return *this;
		};

		inline Quaternion Invert(Liar::Quaternion& e)
		{
			float a0 = x, a1 = y, a2 = z, a3 = w;
			float dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
			float invDot = dot ? 1.0f / dot : 0.0f;
			e[0] = -a0 * invDot;
			e[1] = -a1 * invDot;
			e[2] = -a2 * invDot;
			e[3] = a3 * invDot;
		}

		inline void Identity()
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}

	};

}

