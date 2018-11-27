
#include <math/Vector4.h>
#include <math/Matrix4x4.h>

namespace Liar
{
	void Vector4::Lerp(Liar::Vector4& a, Liar::Vector4& b, Liar::Number t, Liar::Vector4& out)
	{
		Liar::Number ax = a.x, ay = a.y, az = a.z, aw = a.w;
		out.x = ax + t * (b.x - ax);
		out.y = ay + t * (b.y - ay);
		out.z = az + t * (b.z - az);
		out.w = aw + t * (b.w - aw);
	}

	bool Vector4::Equals(const Liar::Vector4& ae, const Liar::Vector4& be)
	{
		return MathUtils3D::NearEqual(abs(ae[0]), abs(be[0])) &&
			MathUtils3D::NearEqual(abs(ae[1]), abs(be[1])) &&
			MathUtils3D::NearEqual(abs(ae[2]), abs(be[2])) &&
			MathUtils3D::NearEqual(abs(ae[3]), abs(be[3]));
	}

	void Vector4::Normalize(const Liar::Vector4& se, Liar::Vector4& oe)
	{
		Liar::Number len = se.Length();
		if (len > 0)
		{
			oe[0] = se[0] * len;
			oe[1] = se[1] * len;
			oe[2] = se[2] * len;
			oe[3] = se[3] * len;
		}
	}

	void Vector4::Add(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
	{
		oe[0] = ae[0] + be[0];
		oe[1] = ae[1] + be[1];
		oe[2] = ae[2] + be[2];
		oe[3] = ae[3] + be[3];
	}

	void Vector4::Subtract(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
	{
		oe[0] = ae[0] - be[0];
		oe[1] = ae[1] - be[1];
		oe[2] = ae[2] - be[2];
		oe[3] = ae[3] - be[3];
	}

	void Vector4::Multiply(const Liar::Vector4& ae, const Liar::Vector4& be, Liar::Vector4& oe)
	{
		oe[0] = ae[0] * be[0];
		oe[1] = ae[1] * be[1];
		oe[2] = ae[2] * be[2];
		oe[3] = ae[3] * be[3];
	}

	void Vector4::Scale(const Liar::Vector4& ae, const Liar::Number b, Liar::Vector4& oe)
	{
		oe[0] = ae[0] * b;
		oe[1] = ae[1] * b;
		oe[2] = ae[2] * b;
		oe[3] = ae[3] * b;
	}

	void Vector4::Clamp(const Liar::Vector4& valuee, const Liar::Vector4& mine, const Liar::Vector4& maxe, Liar::Vector4& oute)
	{
		Liar::Number x = valuee[0], y = valuee[1], z = valuee[2], w = valuee[3];
		Liar::Number mineX = mine[0], mineY = mine[1], mineZ = mine[2], mineW = mine[3];
		Liar::Number maxeX = maxe[0], maxeY = maxe[1], maxeZ = maxe[2], maxeW = maxe[3];

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

	Liar::Number Vector4::DistanceSquared(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
	{
		Liar::Number x = value1e[0] - value2e[0];
		Liar::Number y = value1e[1] - value2e[1];
		Liar::Number z = value1e[2] - value2e[2];
		Liar::Number w = value1e[3] - value2e[3];

		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	Liar::Number Vector4::Distatnce(const Liar::Vector4& value1e, const Liar::Vector4& value2e)
	{
		Liar::Number x = value1e[0] - value2e[0];
		Liar::Number y = value1e[1] - value2e[1];
		Liar::Number z = value1e[2] - value2e[2];
		Liar::Number w = value1e[3] - value2e[3];

		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	Liar::Number Vector4::Dot(const Liar::Vector4& ae, const Liar::Vector4& be)
	{
		return (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]) + (ae[3] * be[3]);
	}

	void Vector4::Min(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e)
	{
		e[0] = std::min(f[0], g[0]);
		e[1] = std::min(f[1], g[1]);
		e[2] = std::min(f[2], g[2]);
		e[3] = std::min(f[3], g[3]);
	}

	void Vector4::Max(const Liar::Vector4& f, const Liar::Vector4& g, Liar::Vector4& e)
	{
		e[0] = std::max(f[0], g[0]);
		e[1] = std::max(f[1], g[1]);
		e[2] = std::max(f[2], g[2]);
		e[3] = std::max(f[3], g[3]);
	}

	void Vector4::TransformByM4x4(const Liar::Vector4& ve, const Liar::Matrix4x4& me, Liar::Vector4& oe)
	{
		Liar::Number vx = ve[0], vy = ve[1], vz = ve[2], vw = ve[3];
		oe[0] = vx * me[0] + vy * me[4] + vz * me[8] + vw * me[12];
		oe[1] = vx * me[1] + vy * me[5] + vz * me[9] + vw * me[13];
		oe[2] = vx * me[2] + vy * me[6] + vz * me[10] + vw * me[14];
		oe[3] = vx * me[3] + vy * me[7] + vz * me[11] + vw * me[15];
	};
}