
#include <math/Matrix3x3.h>
#include <math/Matrix4x4.h>
#include <math/Quaternion.h>
#include <math/MathUtils3D.h>

namespace Liar
{
	bool MathUtils3D::IsZero(Liar::DNumber v)
	{
		return abs(v) < ZERO_TO_LERANCE;
	}

	bool MathUtils3D::NearEqual(Liar::DNumber n1, Liar::DNumber n2)
	{
		return MathUtils3D::IsZero(n1 - n2);
	}

	Liar::DNumber MathUtils3D::FastInvSqrt(Liar::DNumber value)
	{
		if (IsZero(value))
		{
			return value;
		}
		else
		{
			return 1.0 / sqrt(value);
		}
	}

	bool MathUtils3D::IsPOT(Liar::Uint w, Liar::Uint h)
	{
		return (w > 0 && (w & (w - 1)) == 0 && h > 0 && (h & (h - 1)) == 0);
	}

	void MathUtils3D::TransformV3ToV4(const Liar::Vector3& vectorElem, const Liar::Matrix4x4& transformElem, Liar::Vector4& resultElem)
	{
		Liar::Number vectorX = vectorElem[0], vectorY = vectorElem[1], vectorZ = vectorElem[2];

		resultElem[0] = (vectorX * transformElem[0]) + (vectorY * transformElem[4]) + (vectorZ * transformElem[8]) + transformElem[12];
		resultElem[1] = (vectorX * transformElem[1]) + (vectorY * transformElem[5]) + (vectorZ * transformElem[9]) + transformElem[13];
		resultElem[2] = (vectorX * transformElem[2]) + (vectorY * transformElem[6]) + (vectorZ * transformElem[10]) + transformElem[14];
		resultElem[3] = (vectorX * transformElem[3]) + (vectorY * transformElem[7]) + (vectorZ * transformElem[11]) + transformElem[15];
	};

	/**
	* 通过矩阵转换一个三维向量到另外一个三维向量。
	* @param	vector 源三维向量。
	* @param	transform  变换矩阵。
	* @param	result 输出三维向量。
	*/
	void MathUtils3D::TransformV3ToV3(const Liar::Vector3& vector, const Liar::Matrix4x4& transform, Liar::Vector3& result)
	{
		Liar::MathUtils3D::TransformV3ToV4(vector, transform, Liar::MathUtils3D::TEMPVector4);
		result[0] = Liar::MathUtils3D::TEMPVector4[0];
		result[1] = Liar::MathUtils3D::TEMPVector4[1];
		result[2] = Liar::MathUtils3D::TEMPVector4[2];
	}

	void MathUtils3D::TransfromNormal(const Liar::Vector3& normalElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
	{
		Liar::Number normalX = normalElem.x, normalY = normalElem.y, normalZ = normalElem.z;

		resultElem[0] = (normalX * transformElem[0]) + (normalY * transformElem[4]) + (normalZ * transformElem[8]);
		resultElem[1] = (normalX * transformElem[1]) + (normalY * transformElem[5]) + (normalZ * transformElem[9]);
		resultElem[2] = (normalX * transformElem[2]) + (normalY * transformElem[6]) + (normalZ * transformElem[10]);
	};

	void MathUtils3D::TransformCoordinate(const Liar::Vector3& coordinateElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
	{
		Liar::Number coordinateX = coordinateElem.x, coordinateY = coordinateElem.y, coordinateZ = coordinateElem.z;

		Liar::Vector4& vectorElem = Liar::MathUtils3D::TEMPVector4;
		vectorElem[0] = (coordinateX * transformElem[0]) + (coordinateY * transformElem[4]) + (coordinateZ * transformElem[8]) + transformElem[12];
		vectorElem[1] = (coordinateX * transformElem[1]) + (coordinateY * transformElem[5]) + (coordinateZ * transformElem[9]) + transformElem[13];
		vectorElem[2] = (coordinateX * transformElem[2]) + (coordinateY * transformElem[6]) + (coordinateZ * transformElem[10]) + transformElem[14];
		vectorElem[3] = 1.0f / ((coordinateX * transformElem[3]) + (coordinateY * transformElem[7]) + (coordinateZ * transformElem[11]) + transformElem[15]);

		resultElem[0] = vectorElem[0] * vectorElem[3];
		resultElem[1] = vectorElem[1] * vectorElem[3];
		resultElem[2] = vectorElem[2] * vectorElem[3];
	};

	void MathUtils3D::TransformQuat(const Liar::Vector3& se, const Liar::Quaternion& re, Liar::Vector3& destination)
	{
		Liar::Number x = se[0], y = se[1], z = se[2], qx = re[0], qy = re[1], qz = re[2], qw = re[3],
			ix = qw * x + qy * z - qz * y,
			iy = qw * y + qz * x - qx * z,
			iz = qw * z + qx * y - qy * x,
			iw = -qx * x - qy * y - qz * z;

		destination[0] = ix * qw + iw * -qx + iy * -qz - iz * -qy;
		destination[1] = iy * qw + iw * -qy + iz * -qx - ix * -qz;
		destination[2] = iz * qw + iw * -qz + ix * -qy - iy * -qx;
	};

	void MathUtils3D::TransformByM4x4(const Liar::Vector4& ve, const Liar::Matrix4x4& me, Liar::Vector4& oe)
	{
		Liar::Number vx = ve[0], vy = ve[1], vz = ve[2], vw = ve[3];
		oe[0] = vx * me[0] + vy * me[4] + vz * me[8] + vw * me[12];
		oe[1] = vx * me[1] + vy * me[5] + vz * me[9] + vw * me[13];
		oe[2] = vx * me[2] + vy * me[6] + vz * me[10] + vw * me[14];
		oe[3] = vx * me[3] + vy * me[7] + vz * me[11] + vw * me[15];
	};

	/**
	* 通过四元数创建旋转矩阵。
	* @param	rotation 旋转四元数。
	* @param	result 输出旋转矩阵
	*/
	void MathUtils3D::CreateRotationQuaternion(const Liar::Quaternion& rotationE, Liar::Matrix4x4& resultE)
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
	* 从四元数计算旋转矩阵
	* @param	rotation 四元数
	* @param	out 输出矩阵
	*/
	void MathUtils3D::CreateFromQuaternion(const Liar::Quaternion& q, Liar::Matrix4x4& e)
	{
		Liar::Number x = q[0], y = q[1], z = q[2], w = q[3];
		Liar::Number x2 = x + x;
		Liar::Number y2 = y + y;
		Liar::Number z2 = z + z;

		Liar::Number xx = x * x2;
		Liar::Number yx = y * x2;
		Liar::Number yy = y * y2;
		Liar::Number zx = z * x2;
		Liar::Number zy = z * y2;
		Liar::Number zz = z * z2;
		Liar::Number wx = w * x2;
		Liar::Number wy = w * y2;
		Liar::Number wz = w * z2;

		e[0] = 1 - yy - zz;
		e[1] = yx + wz;
		e[2] = zx - wy;
		e[3] = 0;

		e[4] = yx - wz;
		e[5] = 1 - xx - zz;
		e[6] = zy + wx;
		e[7] = 0;

		e[8] = zx + wy;
		e[9] = zy - wx;
		e[10] = 1 - xx - yy;
		e[11] = 0;

		e[12] = 0;
		e[13] = 0;
		e[14] = 0;
		e[15] = 1;
	};

	/**
	* 计算仿射矩阵
	* @param	trans 平移
	* @param	rot 旋转
	* @param	scale 缩放
	* @param	out 输出矩阵
	*/
	void MathUtils3D::CreateAffineTransformation(const Liar::Vector3& te, const Liar::Quaternion& re, const Liar::Vector3& se, Liar::Matrix4x4& oe)
	{
		Liar::Number x = re[0], y = re[1], z = re[2], w = re[3];
		Liar::Number x2 = x + x;
		Liar::Number y2 = y + y;
		Liar::Number z2 = z + z;

		Liar::Number xx = x * x2;
		Liar::Number xy = x * y2;
		Liar::Number xz = x * z2;
		Liar::Number yy = y * y2;
		Liar::Number yz = y * z2;
		Liar::Number zz = z * z2;
		Liar::Number wx = w * x2;
		Liar::Number wy = w * y2;
		Liar::Number wz = w * z2;
		Liar::Number sx = se[0], sy = se[1], sz = se[2];

		oe[0] = (1.0f - (yy + zz)) * sx;
		oe[1] = (xy + wz) * sx;
		oe[2] = (xz - wy) * sx;
		oe[3] = 0.0f;
		oe[4] = (xy - wz) * sy;
		oe[5] = (1.0f - (xx + zz)) * sy;
		oe[6] = (yz + wx) * sy;
		oe[7] = 0.0f;
		oe[8] = (xz + wy) * sz;
		oe[9] = (yz - wx) * sz;
		oe[10] = (1.0f - (xx + yy)) * sz;
		oe[11] = 0.0f;
		oe[12] = te[0];
		oe[13] = te[1];
		oe[14] = te[2];
		oe[15] = 1.0f;
	};

	/**
	* 根据3x3矩阵计算四元数
	* @param	sou 源矩阵
	* @param	out 输出四元数
	*/
	void MathUtils3D::CreateFromMatrix3x3(const Liar::Matrix3x3& f, Liar::Quaternion& e)
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
	void MathUtils3D::CreateFromMatrix4x4(const Liar::Matrix4x4& me, Liar::Quaternion& oe)
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
	void MathUtils3D::RotationMatrix(const Liar::Matrix3x3& me, Liar::Quaternion& oe)
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

	void MathUtils3D::CreateFromMatrix4x4(const Liar::Matrix4x4& sou, Liar::Matrix3x3& out)
	{
		out[0] = sou[0];
		out[1] = sou[1];
		out[2] = sou[2];
		out[3] = sou[4];
		out[4] = sou[5];
		out[5] = sou[6];
		out[6] = sou[8];
		out[7] = sou[9];
		out[8] = sou[10];
	};

	void MathUtils3D::LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Matrix3x3& me)
	{
		Liar::Vector3 v0e, v1e, v2e;
		Vector3::Subtract(eye, target, v0e);
		Vector3::Normalize(v0e, v0e);

		Vector3::Cross(up, v0e, v1e);
		Vector3::Normalize(v1e, v1e);

		Vector3::Cross(v0e, v1e, v2e);

		me[0] = v1e[0];
		me[3] = v1e[1];
		me[6] = v1e[2];

		me[1] = v2e[0];
		me[4] = v2e[1];
		me[7] = v2e[2];

		me[2] = v0e[0];
		me[5] = v0e[1];
		me[8] = v0e[2];
	}

	const Liar::DNumber MathUtils3D::MAX_VALUE = 3.40282347e+38;
	const Liar::DNumber MathUtils3D::MIN_VALUE = -3.40282347e+38;
	const Liar::DNumber MathUtils3D::ZERO_TO_LERANCE = 1e-6;
	const Liar::Number MathUtils3D::PI = 3.1415926f;
	const Liar::Number MathUtils3D::AngleToRandin = 180 / MathUtils3D::PI;
	const Liar::Number MathUtils3D::RandinToAngle = MathUtils3D::PI / 180;

	const Liar::Vector3 MathUtils3D::ZERO = Liar::Vector3(0.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::ONE = Liar::Vector3(1.0f, 1.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::NegativeUnitX = Liar::Vector3(-1.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitX = Liar::Vector3(1.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitY = Liar::Vector3(0.0f, 1.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitZ = Liar::Vector3(0.0f, 0.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::ForwardRH = Liar::Vector3(0.0f, 0.0f, -1.0f);
	const Liar::Vector3 MathUtils3D::ForwardLH = Liar::Vector3(0.0f, 0.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::Up = Liar::Vector3(0.0f, 1.0f, 0.0f);
	const Liar::Quaternion MathUtils3D::TEMP_QUA = Liar::Quaternion();

	Liar::Vector3 MathUtils3D::TEMPVector30 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector31 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector32 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector33 = Liar::Vector3();
	Liar::Matrix4x4 MathUtils3D::TEMPMatrix0 = Liar::Matrix4x4();
	Liar::Matrix4x4 MathUtils3D::TEMPMatrix1 = Liar::Matrix4x4();
	Liar::Matrix3x3 MathUtils3D::TEMPMatrix3x3 = Liar::Matrix3x3();
	Liar::Vector4 MathUtils3D::TEMPVector4 = Liar::Vector4();
	Liar::Quaternion MathUtils3D::TEMPQuaternion0 = Liar::Quaternion();
}