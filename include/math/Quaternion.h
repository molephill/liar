#pragma once

#include "Vector4.h"

namespace Liar
{
	class Quaternion:public Vector4
	{
	public:
		Quaternion(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number cz = 0.0f, Liar::Number cw = 1.0f) { Liar::Vector4::Set(cx, cy, cz, cw); };
		~Quaternion() {};

	public:
		/**
		*  从欧拉角生成四元数（顺序为Yaw、Pitch、Roll）
		* @param	yaw yaw值
		* @param	pitch pitch值
		* @param	roll roll值
		* @param	out 输出四元数
		*/
		static void CreateFromYawPitchRoll(Liar::Number yaw, Liar::Number pitch, Liar::Number roll, Liar::Quaternion& oe)
		{
			Liar::Number halfRoll = roll * 0.5f;
			Liar::Number halfPitch = pitch * 0.5f;
			Liar::Number halfYaw = yaw * 0.5f;

			Liar::Number sinRoll = sinf(halfRoll);
			Liar::Number cosRoll = cosf(halfRoll);
			Liar::Number sinPitch = sinf(halfPitch);
			Liar::Number cosPitch = cosf(halfPitch);
			Liar::Number sinYaw = sinf(halfYaw);
			Liar::Number cosYaw = cosf(halfYaw);

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
			Liar::Number lx = le[0], ly = le[1], lz = le[2], lw = le[3];
			Liar::Number rx = re[0], ry = re[1], rz = re[2], rw = re[3];

			Liar::Number a = (ly * rz - lz * ry);
			Liar::Number b = (lz * rx - lx * rz);
			Liar::Number c = (lx * ry - ly * rx);
			Liar::Number d = (lx * rx + ly * ry + lz * rz);

			oe[0] = (lx * rw + rx * lw) + a;
			oe[1] = (ly * rw + ry * lw) + b;
			oe[2] = (lz * rw + rz * lw) + c;
			oe[3] = lw * rw - d;
		};

		static Liar::Number ArcTanAngle(Liar::Number x, Liar::Number y)
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
		static void CreateFromAxisAngle(const Liar::Vector3& axis, Liar::Number rad, Liar::Quaternion& e)
		{
			Liar::Number halfRad = rad * 0.5f;
			Liar::Number s = sinf(rad);
			e[0] = s * axis[0];
			e[1] = s * axis[1];
			e[2] = s * axis[2];
			e[3] = cosf(rad);
		};

		/**
		* 球面插值
		* @param	left left四元数
		* @param	right  right四元数
		* @param	a 插值比例
		* @param	out 输出四元数
		* @return
		*/
		static void Slert(const Liar::Quaternion& a, const Liar::Quaternion& b, Liar::Number t, Liar::Quaternion& oe)
		{
			Liar::Number ax = a[0], ay = a[1], az = a[2], aw = a[3];
			Liar::Number bx = b[0], by = a[1], bz = a[2], bw = b[3];

			Liar::Number omega = 0.0f, cosom = 0.0f, sinom = 0.0f, scale0 = 0.0f, scale1 = 0.0f;
			// calc cosine 
			cosom = ax * bx + ay * by + az * bz + aw * bw;
			// adjust signs (if necessary) 
			if (cosom < 0.0f) 
			{
				cosom = -cosom;
				bx = -bx;
				by = -by;
				bz = -bz;
				bw = -bw;
			}
			// calculate coefficients 
			if ((1.0f - cosom) > 0.000001f) 
			{
				// standard case (slerp) 
				omega = acosf(cosom);
				sinom = sinf(omega);
				scale0 = sinf((1.0f - t) * omega) / sinom;
				scale1 = sinf(t * omega) / sinom;
			}
			else 
			{
				// "from" and "to" quaternions are very close  
				//  ... so we can do a linear interpolation 
				scale0 = 1.0f - t;
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
		static void Lerp(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Number t, Liar::Quaternion& e)
		{
			Liar::Number ax = f[0], ay = f[1], az = f[2], aw = f[3];
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
		static Liar::Number Dot(const Liar::Quaternion& f, const Liar::Quaternion& g)
		{
			return f[0] * g[0] + f[1] * g[1] + f[2] * g[2] + f[3] * g[3];
		};

		/**
		* 计算观察四元数
		* @param	eye    观察者位置
		* @param	target 目标位置
		* @param	up     上向量
		* @param	out    输出四元数
		*/
		static void LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Quaternion& out)
		{
			Liar::MathUtils3D::LookAt(eye, target, up, Liar::MathUtils3D::TEMPMatrix3x3);
			Liar::MathUtils3D::RotationMatrix(Liar::MathUtils3D::TEMPMatrix3x3, out);
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
			Liar::Number lengthSq = vE.LengthSquared();
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
			Liar::MathUtils3D::TransformQuat(Liar::MathUtils3D::ForwardRH, *this, Liar::MathUtils3D::TEMPVector31);
			Liar::MathUtils3D::TransformQuat(Liar::MathUtils3D::Up, *this, Liar::MathUtils3D::TEMPVector32);
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
				Liar::MathUtils3D::CreateRotationY(-anglee[1], Liar::MathUtils3D::TEMPMatrix0);
				Liar::MathUtils3D::CreateRotationX(-anglee[0], Liar::MathUtils3D::TEMPMatrix1);

				Liar::MathUtils3D::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector32);
				Liar::MathUtils3D::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix1, Liar::MathUtils3D::TEMPVector32);
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
			Liar::Number a0 = x, a1 = y, a2 = z, a3 = w;
			Liar::Number dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
			Liar::Number invDot = dot ? 1.0f / dot : 0.0f;
			x = -a0 * invDot;
			y = -a1 * invDot;
			z = -a2 * invDot;
			w = a3 * invDot;
			return *this;
		};

		inline Quaternion Invert(Liar::Quaternion& e)
		{
			Liar::Number a0 = x, a1 = y, a2 = z, a3 = w;
			Liar::Number dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
			Liar::Number invDot = dot ? 1.0f / dot : 0.0f;
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

