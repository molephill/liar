
#include <math/Quaternion.h>
#include <math/Vector3.h>
#include <math/Matrix4x4.h>
#include <math/Matrix3x3.h>

namespace Liar
{
	/**
	*  从欧拉角生成四元数（顺序为Yaw、Pitch、Roll）
	* @param	yaw yaw值
	* @param	pitch pitch值
	* @param	roll roll值
	* @param	out 输出四元数
	*/
	void Quaternion::CreateFromYawPitchRoll(Liar::Number yaw, Liar::Number pitch, Liar::Number roll, Liar::Quaternion& oe)
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
	}

	/**
	* 计算两个四元数相乘
	* @param	left left四元数
	* @param	right  right四元数
	* @param	out 输出四元数
	*/
	void Quaternion::Multiply(const Liar::Quaternion& le, const Liar::Quaternion& re, Liar::Quaternion & oe)
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
	}

	Liar::Number Quaternion::ArcTanAngle(Liar::Number x, Liar::Number y)
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

	void Quaternion::AngleTo(const Liar::Vector3& from, const Liar::Vector3& location, Liar::Vector3& angle)
	{
		Liar::Vector3& TEMPVector30 = MathUtils3D::TEMPVector30;
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
	void Quaternion::CreateFromAxisAngle(const Liar::Vector3& axis, Liar::Number rad, Liar::Quaternion& e)
	{
		Liar::Number halfRad = rad * 0.5f;
		Liar::Number s = sinf(rad);
		e[0] = s * axis[0];
		e[1] = s * axis[1];
		e[2] = s * axis[2];
		e[3] = cosf(rad);
	}

	/**
	* 球面插值
	* @param	left left四元数
	* @param	right  right四元数
	* @param	a 插值比例
	* @param	out 输出四元数
	* @return
	*/
	void Quaternion::Slert(const Liar::Quaternion& a, const Liar::Quaternion& b, Liar::Number t, Liar::Quaternion& oe)
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
	}

	/**
	* 计算两个四元数的线性插值
	* @param	left left四元数
	* @param	right right四元数b
	* @param	t 插值比例
	* @param	out 输出四元数
	*/
	void Quaternion::Lerp(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Number t, Liar::Quaternion& e)
	{
		Liar::Number ax = f[0], ay = f[1], az = f[2], aw = f[3];
		e[0] = ax + t * (g[0] - ax);
		e[1] = ay + t * (g[1] - ay);
		e[2] = az + t * (g[2] - az);
		e[3] = aw + t * (g[3] - aw);
	}

	/**
	* 计算两个四元数的和
	* @param	left  left四元数
	* @param	right right 四元数
	* @param	out 输出四元数
	*/
	void Quaternion::Add(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Quaternion& e)
	{
		e[0] = f[0] + g[0];
		e[1] = f[1] + g[1];
		e[2] = f[2] + g[2];
		e[3] = f[3] + g[3];
	}

	/**
	* 计算两个四元数的点积
	* @param	left left四元数
	* @param	right right四元数
	* @return  点积
	*/
	Liar::Number Quaternion::Dot(const Liar::Quaternion& f, const Liar::Quaternion& g)
	{
		return f[0] * g[0] + f[1] * g[1] + f[2] * g[2] + f[3] * g[3];
	}

	/**
	* 计算观察四元数
	* @param	eye    观察者位置
	* @param	target 目标位置
	* @param	up     上向量
	* @param	out    输出四元数
	*/
	void Quaternion::LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Quaternion& out)
	{
		Liar::Matrix3x3::LookAt(eye, target, up, Liar::MathUtils3D::TEMPMatrix3x3);
		Liar::Quaternion::RotationMatrix(Liar::MathUtils3D::TEMPMatrix3x3, out);
	}

	/**
	* 计算旋转观察四元数
	* @param	forward 方向
	* @param	up     上向量
	* @param	out    输出四元数
	*/
	void Quaternion::RotationLookAt(const Liar::Vector3& forward, const Liar::Vector3& up, Liar::Quaternion& out)
	{
		LookAt(Liar::MathUtils3D::ZERO, forward, up, out);
	}

	/**
	* 计算四元数的逆四元数。
	* @param	value 四元数。
	* @param	out 逆四元数。
	*/
	void Quaternion::Invert(const Liar::Quaternion& vE, Liar::Quaternion& oE)
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

	/**
	* 分解四元数到欧拉角（顺序为Yaw、Pitch、Roll），参考自http://xboxforums.create.msdn.com/forums/p/4574/23988.aspx#23988,问题绕X轴翻转超过±90度时有，会产生瞬间反转
	* @param	quaternion 源四元数
	* @param	out 欧拉角值
	*/
	void Quaternion::GetYawPitchRoll(Liar::Vector3& oe)
	{
		Liar::Vector3::TransformQuat(Liar::MathUtils3D::ForwardRH, *this, Liar::MathUtils3D::TEMPVector31);
		Liar::Vector3::TransformQuat(Liar::MathUtils3D::Up, *this, Liar::MathUtils3D::TEMPVector32);
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
			Liar::Matrix4x4::CreateRotationY(-anglee[1], Liar::MathUtils3D::TEMPMatrix0);
			Liar::Matrix4x4::CreateRotationX(-anglee[0], Liar::MathUtils3D::TEMPMatrix1);

			Liar::Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector32);
			Liar::Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector32, Liar::MathUtils3D::TEMPMatrix1, Liar::MathUtils3D::TEMPVector32);
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
	}

	/**
	* 通过四元数创建旋转矩阵。
	* @param	rotation 旋转四元数。
	* @param	result 输出旋转矩阵
	*/
	void Quaternion::CreateRotationQuaternion(const Liar::Quaternion& rotationE, Liar::Matrix4x4& resultE)
	{
		Liar::Number rotationX = rotationE[0], rotationY = rotationE[1], rotationZ = rotationE[2], rotationW = rotationE[3];
		Liar::Number xx = rotationX * rotationX;
		Liar::Number yy = rotationY * rotationY;
		Liar::Number zz = rotationZ * rotationZ;
		Liar::Number xy = rotationX * rotationY;
		Liar::Number zw = rotationZ * rotationW;
		Liar::Number zx = rotationZ * rotationX;
		Liar::Number yw = rotationY * rotationW;
		Liar::Number yz = rotationY * rotationZ;
		Liar::Number xw = rotationX * rotationW;

		resultE[3] = resultE[7] = resultE[11] = resultE[12] = resultE[13] = resultE[14] = 0.0f;
		resultE[15] = 1.0f;
		resultE[0] = 1.0f - (2.0f * (yy + zz));
		resultE[1] = 2.0f * (xy + zw);
		resultE[2] = 2.0f * (zx - yw);
		resultE[4] = 2.0f * (xy - zw);
		resultE[5] = 1.0f - (2.0f * (zz + xx));
		resultE[6] = 2.0f * (yz + xw);
		resultE[8] = 2.0f * (zx + yw);
		resultE[9] = 2.0f * (yz - xw);
		resultE[10] = 1.0f - (2.0f * (yy + xx));
	};

	/**
	* 根据3x3矩阵计算四元数
	* @param	sou 源矩阵
	* @param	out 输出四元数
	*/
	void Quaternion::CreateFromMatrix3x3(const Liar::Matrix3x3& f, Liar::Quaternion& e)
	{
		Liar::Number fTrace = f[0] + f[4] + f[8];
		Liar::Number fRoot = 0.0f;
		if (fTrace > 0.0f) {
			// |w| > 1/2, may as well choose w > 1/2
			fRoot = sqrtf(fTrace + 1.0f);  // 2w
			e[3] = 0.5f * fRoot;
			fRoot = 0.5f / fRoot;  // 1/(4w)
			e[0] = (f[5] - f[7]) * fRoot;
			e[1] = (f[6] - f[2]) * fRoot;
			e[2] = (f[1] - f[3]) * fRoot;
		}
		else
		{
			// |w| <= 1/2                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
			int i = 0;
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

			fRoot = sqrtf(f[i * 3 + i] - f[j * 3 + j] - f[k * 3 + k] + 1.0f);
			e[i] = 0.5f * fRoot;
			fRoot = 0.5f / fRoot;
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
	void Quaternion::CreateFromMatrix4x4(const Liar::Matrix4x4& me, Liar::Quaternion& oe)
	{
		Liar::Number sqrt = 0.0f, half = 0.0f;
		Liar::Number scale = me[0] + me[5] + me[10];
		if (scale > 0.0f)
		{
			sqrt = sqrtf(scale + 1.0f);
			oe[3] = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			oe[0] = (me[6] - me[9]) * sqrt;
			oe[1] = (me[8] - me[2]) * sqrt;
			oe[2] = (me[1] - me[4]) * sqrt;
		}
		else if ((me[0] >= me[5]) && (me[0] >= me[10]))
		{
			sqrt = sqrtf(1.0f + me[0] - me[5] - me[10]);
			half = 0.5f / sqrt;

			oe[0] = 0.5f * sqrt;
			oe[1] = (me[1] + me[4]) * half;
			oe[2] = (me[2] + me[8]) * half;
			oe[3] = (me[6] - me[9]) * half;
		}
		else if (me[5] > me[10])
		{
			sqrt = sqrtf(1.0f + me[5] - me[0] - me[10]);
			half = 0.5f / sqrt;

			oe[0] = (me[4] + me[1]) * half;
			oe[1] = 0.5f * sqrt;
			oe[2] = (me[9] + me[6]) * half;
			oe[3] = (me[8] - me[2]) * half;
		}
		else
		{
			sqrt = sqrtf(1.0f + me[10] - me[0] - me[5]);
			half = 0.5f / sqrt;

			oe[0] = (me[8] + me[2]) * half;
			oe[1] = (me[9] + me[6]) * half;
			oe[2] = 0.5f * sqrt;
			oe[3] = (me[1] - me[4]) * half;
		}
	};

	/**
	* 通过一个3x3矩阵创建一个四元数
	* @param	matrix3x3  3x3矩阵
	* @param	out        四元数
	*/
	void Quaternion::RotationMatrix(const Liar::Matrix3x3& me, Liar::Quaternion& oe)
	{
		Liar::Number m11 = me[0];
		Liar::Number m12 = me[1];
		Liar::Number m13 = me[2];
		Liar::Number m21 = me[3];
		Liar::Number m22 = me[4];
		Liar::Number m23 = me[5];
		Liar::Number m31 = me[6];
		Liar::Number m32 = me[7];
		Liar::Number m33 = me[8];

		Liar::Number sqrt = 0, half = 0;
		Liar::Number scale = m11 + m22 + m33;

		if (scale > 0)
		{
			sqrt = sqrtf(scale + 1);
			oe[3] = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			oe[0] = (m23 - m32) * sqrt;
			oe[1] = (m31 - m13) * sqrt;
			oe[2] = (m12 - m21) * sqrt;
		}
		else if ((m11 >= m22) && (m11 >= m33))
		{
			sqrt = sqrtf(1 + m11 - m22 - m33);
			half = 0.5f / sqrt;

			oe[0] = 0.5f * sqrt;
			oe[1] = (m12 + m21) * half;
			oe[2] = (m13 + m31) * half;
			oe[3] = (m23 - m32) * half;
		}
		else if (m22 > m33)
		{
			sqrt = sqrtf(1 + m22 - m11 - m33);
			half = 0.5f / sqrt;

			oe[0] = (m21 + m12) * half;
			oe[1] = 0.5f * sqrt;
			oe[2] = (m32 + m23) * half;
			oe[3] = (m31 - m13) * half;
		}
		else
		{
			sqrt = sqrtf(1 + m33 - m11 - m22);
			half = 0.5f / sqrt;

			oe[0] = (m31 + m13) * half;
			oe[1] = (m32 + m23) * half;
			oe[2] = 0.5f * sqrt;
			oe[3] = (m12 - m21) * half;
		}
	}

	/**
	* 求四元数的逆
	* @param	out  输出四元数
	*/
	Quaternion& Quaternion::Invert()
	{
		Liar::Number a0 = x, a1 = y, a2 = z, a3 = w;
		Liar::Number dot = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
		Liar::Number invDot = dot ? 1.0f / dot : 0.0f;
		x = -a0 * invDot;
		y = -a1 * invDot;
		z = -a2 * invDot;
		w = a3 * invDot;
		return *this;
	}
}