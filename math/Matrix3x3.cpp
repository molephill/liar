
#include <math/Matrix3x3.h>
#include <math/Matrix4x4.h>

namespace Liar
{
	void Matrix3x3::CreateFromTranslation(const Liar::Vector2& g, Liar::Matrix3x3& out)
	{
		out[0] = 1;
		out[1] = 0;
		out[2] = 0;
		out[3] = 0;
		out[4] = 1;
		out[5] = 0;
		out[6] = g[0];
		out[7] = g[1];
		out[8] = 1;
	}

	void Matrix3x3::CreateFromRotation(Liar::Number rad, Liar::Matrix3x3& e)
	{
		Liar::Number s = sinf(rad), c = cosf(rad);
		e[0] = c;
		e[1] = s;
		e[2] = 0;

		e[3] = -s;
		e[4] = c;
		e[5] = 0;

		e[6] = 0;
		e[7] = 0;
		e[8] = 1;
	}

	void Matrix3x3::CreateFromScaling(const Liar::Vector2& g, Liar::Matrix3x3& e)
	{
		e[0] = g[0];
		e[1] = 0;
		e[2] = 0;

		e[3] = 0;
		e[4] = g[1];
		e[5] = 0;

		e[6] = 0;
		e[7] = 0;
		e[8] = 1;
	}

	void Matrix3x3::Multiply(const Liar::Matrix3x3& f, const Liar::Matrix3x3& g, Liar::Matrix3x3& e)
	{
		Liar::Number a00 = f[0], a01 = f[1], a02 = f[2];
		Liar::Number a10 = f[3], a11 = f[4], a12 = f[5];
		Liar::Number a20 = f[6], a21 = f[7], a22 = f[8];

		Liar::Number b00 = g[0], b01 = g[1], b02 = g[2];
		Liar::Number b10 = g[3], b11 = g[4], b12 = g[5];
		Liar::Number b20 = g[6], b21 = g[7], b22 = g[8];

		e[0] = b00 * a00 + b01 * a10 + b02 * a20;
		e[1] = b00 * a01 + b01 * a11 + b02 * a21;
		e[2] = b00 * a02 + b01 * a12 + b02 * a22;

		e[3] = b10 * a00 + b11 * a10 + b12 * a20;
		e[4] = b10 * a01 + b11 * a11 + b12 * a21;
		e[5] = b10 * a02 + b11 * a12 + b12 * a22;

		e[6] = b20 * a00 + b21 * a10 + b22 * a20;
		e[7] = b20 * a01 + b21 * a11 + b22 * a21;
		e[8] = b20 * a02 + b21 * a12 + b22 * a22;
	}

	void Matrix3x3::Invert(const Liar::Matrix3x3& m, Liar::Matrix3x3& e)
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
			e[0] = b01 * det;
			e[1] = (-a22 * a01 + a02 * a21) * det;
			e[2] = (a12 * a01 - a02 * a11) * det;
			e[3] = b11 * det;
			e[4] = (a22 * a00 - a02 * a20) * det;
			e[5] = (-a12 * a00 + a02 * a10) * det;
			e[6] = b21 * det;
			e[7] = (-a21 * a00 + a01 * a20) * det;
			e[8] = (a11 * a00 - a01 * a10) * det;
		}
	}

	void Matrix3x3::Transpose(const Liar::Matrix3x3& f, Liar::Matrix3x3& e)
	{
		if (&e == &f)
		{
			Liar::Number a01 = f[1], a02 = f[2], a12 = f[5];
			e[1] = f[3];
			e[2] = f[6];
			e[3] = a01;
			e[5] = f[7];
			e[6] = a02;
			e[7] = a12;
		}
		else
		{
			e[0] = f[0];
			e[1] = f[3];
			e[2] = f[6];
			e[3] = f[1];
			e[4] = f[4];
			e[5] = f[7];
			e[6] = f[2];
			e[7] = f[5];
			e[8] = f[8];
		}
	}

	void Matrix3x3::CreateFromMatrix4x4(const Liar::Matrix4x4& sou, Liar::Matrix3x3& out)
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

	void Matrix3x3::LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Matrix3x3& me)
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
}