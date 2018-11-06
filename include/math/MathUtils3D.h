#pragma once

#include <algorithm>
#include <LiarType.h>

#include "Matrix4x4.h";
#include "Matrix3x3.h"

namespace Liar
{
	class MathUtils3D
	{
	public:
		static const Liar::DNumber MAX_VALUE;
		static const Liar::DNumber MIN_VALUE;
		static const Liar::DNumber ZERO_TO_LERANCE;
		static const Liar::DNumber PI;

	public:
		static const Liar::Vector3 ZERO;
		static const Liar::Vector3 ONE;
		static const Liar::Vector3 NegativeUnitX;
		static const Liar::Vector3 UnitX;
		static const Liar::Vector3 UnitY;
		static const Liar::Vector3 UnitZ;
		static const Liar::Vector3 ForwardRH;
		static const Liar::Vector3 ForwardLH;
		static const Liar::Vector3 Up;
		static const Liar::Quaternion DEFAULT_QUA;

	public:
		static Liar::Vector3 TEMPVector30;
		static Liar::Vector3 TEMPVector31;
		static Liar::Vector3 TEMPVector32;
		static Liar::Vector3 TEMPVector33;
		static Liar::Matrix4x4 TEMPMatrix0;
		static Liar::Matrix4x4 TEMPMatrix1;
		static Liar::Matrix3x3 TEMPMatrix3x3;
		static Liar::Vector4 TEMPVector4;

	public:
		static bool IsZero(double v)
		{
			return abs(v) < ZERO_TO_LERANCE;
		}

		static bool NearEqual(double n1, double n2)
		{
			return IsZero(n1 - n2);
		}

		static double FastInvSqrt(double value)
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
	};

	const Liar::DNumber MathUtils3D::MAX_VALUE = 3.40282347e+38;
	const Liar::DNumber MathUtils3D::MIN_VALUE = -3.40282347e+38;
	const Liar::DNumber MathUtils3D::ZERO_TO_LERANCE = 1e-6;
	const Liar::DNumber MathUtils3D::PI = 3.1415926;

	const Liar::Vector3 MathUtils3D::ZERO = Liar::Vector3(0.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::ONE = Liar::Vector3(1.0f, 1.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::NegativeUnitX = Liar::Vector3(-1.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitX = Liar::Vector3(1.0f, 0.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitY = Liar::Vector3(0.0f, 1.0f, 0.0f);
	const Liar::Vector3 MathUtils3D::UnitZ = Liar::Vector3(0.0f, 0.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::ForwardRH = Liar::Vector3(0.0f, 0.0f, -1.0f);
	const Liar::Vector3 MathUtils3D::ForwardLH = Liar::Vector3(0.0f, 0.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::Up = Liar::Vector3(0.0f, 1.0f, 0.0f);
	const Liar::Quaternion MathUtils3D::DEFAULT_QUA = Liar::Quaternion();

	Liar::Vector3 MathUtils3D::TEMPVector30 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector31 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector32 = Liar::Vector3();
	Liar::Vector3 MathUtils3D::TEMPVector33 = Liar::Vector3();
	Liar::Matrix4x4 MathUtils3D::TEMPMatrix0 = Liar::Matrix4x4();
	Liar::Matrix4x4 MathUtils3D::TEMPMatrix1 = Liar::Matrix4x4();
	Liar::Matrix3x3 MathUtils3D::TEMPMatrix3x3 = Liar::Matrix3x3();
	Liar::Vector4 MathUtils3D::TEMPVector4 = Liar::Vector4();

}