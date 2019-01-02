#pragma once

#include <LiarType.h>

namespace Liar
{
	class Vector3;
	class Vector4;
	class Quaternion;
	class Matrix3x3;
	class Matrix4x4;

	class MathUtils3D
	{
	public:
		static const Liar::DNumber MAX_VALUE;
		static const Liar::DNumber MIN_VALUE;
		static const Liar::DNumber ZERO_TO_LERANCE;
		static const Liar::Number PI;
		static const Liar::Number AngleToRandin;
		static const Liar::Number RandinToAngle;

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
		static const Liar::Quaternion TEMP_QUA;

	public:
		static Liar::Vector3 TEMPVector30;
		static Liar::Vector3 TEMPVector31;
		static Liar::Vector3 TEMPVector32;
		static Liar::Vector3 TEMPVector33;
		static Liar::Matrix4x4 TEMPMatrix0;
		static Liar::Matrix4x4 TEMPMatrix1;
		static Liar::Matrix3x3 TEMPMatrix3x3;
		static Liar::Vector4 TEMPVector4;
		static Liar::Quaternion TEMPQuaternion0;

	public:
		static bool IsZero(Liar::DNumber);
		static bool NearEqual(Liar::DNumber, Liar::DNumber);
		static Liar::DNumber FastInvSqrt(Liar::DNumber);
		static bool IsPOT(Liar::Uint, Liar::Uint);
		static void ReadString(std::string&, FILE*);
		static std::string ReadString(FILE*);
	};

}