
#include <math/Vector3.h>
#include <math/Matrix4x4.h>
#include <math/Quaternion.h>
#include <math/Vector3.h>

namespace Liar
{
	Liar::Number Vector3::DistanceSquared(const Liar::Vector3& value1, const Liar::Vector3& value2)
	{
		Liar::Number tmpx = value1.x - value2.x;
		Liar::Number tmpy = value1.y - value2.y;
		Liar::Number tmpz = value1.z - value2.z;
		return tmpx * tmpx + tmpy * tmpy + tmpz * tmpz;
	}

	Liar::Number Vector3::Distance(const Liar::Vector3& value1, const Liar::Vector3& value2)
	{
		Liar::Number tmpx = value1.x - value2.x;
		Liar::Number tmpy = value1.y - value2.y;
		Liar::Number tmpz = value1.z - value2.z;
		return sqrtf(tmpx * tmpx + tmpy * tmpy + tmpz * tmpz);
	}

	void Vector3::Min(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out)
	{
		out.x = std::min(a.x, b.x);
		out.y = std::min(a.y, b.y);
		out.z = std::min(a.z, b.z);
	}

	void Vector3::Max(const Liar::Vector3& a, const Liar::Vector3& b, Liar::Vector3& out)
	{
		out.x = std::max(a.x, b.x);
		out.y = std::max(a.y, b.y);
		out.z = std::max(a.z, b.z);
	}

	Liar::Number Vector3::ScalarLength(const Liar::Vector3& f)
	{
		return sqrt(f.x*f.x + f.y*f.y + f.z*f.z);
	}

	Liar::Number Vector3::ScalarLengthSquared(const Liar::Vector3& f)
	{
		return f.x*f.x + f.y*f.y + f.z*f.z;
	}

	void Vector3::Normalize(const Liar::Vector3& se, Liar::Vector3& oe)
	{
		Liar::Number len = se.x*se.x + se.y*se.y + se.z*se.z;
		if (len > 0)
		{
			len = static_cast<Liar::Number>(1.0 / sqrtf(len));
			oe[0] = se[0] * len;
			oe[1] = se[1] * len;
			oe[2] = se[2] * len;
		}
	}

	void Vector3::Multiply(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e)
	{
		e[0] = f[0] * g[0];
		e[1] = f[1] * g[1];
		e[2] = f[2] * g[2];
	}

	void Vector3::Scale(const Liar::Vector3& f, const Liar::Number b, Liar::Vector3& e)
	{
		e[0] = f[0] * b;
		e[1] = f[1] * b;
		e[2] = f[2] * b;
	}

	void Vector3::Lerp(const Liar::Vector3& f, const Liar::Vector3& g, const Liar::Number t, Liar::Vector3& e)
	{
		Liar::Number ax = f.x, ay = f.y, az = f.z;
		e[0] = ax + t * (g[0] - ax);
		e[1] = ay + t * (g[1] - ay);
		e[2] = az + t * (g[2] - az);
	}

	void Vector3::Clamp(const Liar::Vector3& valuee, const Liar::Vector3& mine, const Liar::Vector3& maxe, Liar::Vector3& oute)
	{
		Liar::Number x = valuee.x, y = valuee.y, z = valuee.z;
		Liar::Number mineX = mine.x, mineY = mine.y, mineZ = mine.z;
		Liar::Number maxeX = maxe.x, maxeY = maxe.y, maxeZ = maxe.z;

		x = (x > maxeX) ? maxeX : x;
		x = (x < mineX) ? mineX : x;

		y = (y > maxeY) ? maxeY : y;
		y = (y < mineY) ? mineY : y;

		z = (z > maxeZ) ? maxeZ : z;
		z = (z < mineZ) ? mineZ : z;

		oute[0] = x;
		oute[1] = y;
		oute[2] = z;
	}

	void Vector3::Add(const Liar::Vector3& f, const Liar::Vector3& g, Liar::Vector3& e)
	{
		e[0] = f[0] + g[0];
		e[1] = f[1] + g[1];
		e[2] = f[2] + g[2];
	}

	void Vector3::Subtract(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe)
	{
		oe[0] = ae[0] - be[0];
		oe[1] = ae[1] - be[1];
		oe[2] = ae[2] - be[2];
	}

	void Vector3::Cross(const Liar::Vector3& ae, const Liar::Vector3& be, Liar::Vector3& oe)
	{
		Liar::Number ax = ae.x, ay = ae.y, az = ae.z,
			bx = be.x, by = be.y, bz = be.z;
		oe[0] = ay * bz - az * by;
		oe[1] = az * bx - ax * bz;
		oe[2] = ax * by - ay * bx;
	}

	Liar::Number Vector3::Dot(const Liar::Vector3& ae, const Liar::Vector3& be)
	{
		return (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]);
	}

	bool Vector3::Equals(const Liar::Vector3& ae, const Liar::Vector3& be)
	{
		return MathUtils3D::NearEqual(abs(ae[0]), abs(be[0])) && MathUtils3D::NearEqual(abs(ae[1]), abs(be[1])) && MathUtils3D::NearEqual(abs(ae[2]), abs(be[2]));
	}

	void Vector3::TransformV3ToV4(const Liar::Vector3& vectorElem, const Liar::Matrix4x4& transformElem, Liar::Vector4& resultElem)
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
	void Vector3::TransformV3ToV3(const Liar::Vector3& vector, const Liar::Matrix4x4& transform, Liar::Vector3& result)
	{
		Liar::Vector3::TransformV3ToV4(vector, transform, Liar::MathUtils3D::TEMPVector4);
		result[0] = Liar::MathUtils3D::TEMPVector4[0];
		result[1] = Liar::MathUtils3D::TEMPVector4[1];
		result[2] = Liar::MathUtils3D::TEMPVector4[2];
	}

	void Vector3::TransfromNormal(const Liar::Vector3& normalElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
	{
		Liar::Number normalX = normalElem.x, normalY = normalElem.y, normalZ = normalElem.z;

		resultElem[0] = (normalX * transformElem[0]) + (normalY * transformElem[4]) + (normalZ * transformElem[8]);
		resultElem[1] = (normalX * transformElem[1]) + (normalY * transformElem[5]) + (normalZ * transformElem[9]);
		resultElem[2] = (normalX * transformElem[2]) + (normalY * transformElem[6]) + (normalZ * transformElem[10]);
	};

	void Vector3::TransformCoordinate(const Liar::Vector3& coordinateElem, const Liar::Matrix4x4& transformElem, Liar::Vector3& resultElem)
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

	void Vector3::TransformQuat(const Liar::Vector3& se, const Liar::Quaternion& re, Liar::Vector3& destination)
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
}