#pragma once

#include <algorithm>
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

		// ======================= vector3 =============================
		static void TransformV3ToV4(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector4&);
		static void TransformV3ToV3(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransfromNormal(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransformCoordinate(const Liar::Vector3&, const Liar::Matrix4x4&, Liar::Vector3&);
		static void TransformQuat(const Liar::Vector3&, const Liar::Quaternion&, Liar::Vector3&);

		// ====================== vector4 =====================
		static void TransformByM4x4(const Liar::Vector4&, const Liar::Matrix4x4&, Liar::Vector4&);

		// ====================== quaternion ==================
		static void CreateRotationQuaternion(const Liar::Quaternion&, Liar::Matrix4x4&);
		static void CreateFromMatrix3x3(const Liar::Matrix3x3&, Liar::Quaternion&);
		static void CreateFromMatrix4x4(const Liar::Matrix4x4&, Liar::Quaternion&);
		static void RotationMatrix(const Liar::Matrix3x3&, Liar::Quaternion&);

		// ====================== matrix4x4 ==================
		static void CreateFromQuaternion(const Liar::Quaternion&, Liar::Matrix4x4&);
		static void CreateAffineTransformation(const Liar::Vector3&, const Liar::Quaternion&, const Liar::Vector3&, Liar::Matrix4x4&);

		// ====================== matrix3x3 ==================
		static void CreateFromMatrix4x4(const Liar::Matrix4x4&, Liar::Matrix3x3&);
		static void LookAt(const Liar::Vector3&, const Liar::Vector3&, const Liar::Vector3&, Liar::Matrix3x3&);
	};

}