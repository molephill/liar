
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

	void MathUtils3D::ReadString(std::string& s, FILE* pFile)
	{
		s = "";

		size_t szChar = sizeof(Liar::Char);
		size_t strip = sizeof(Liar::Int);

		Liar::Int szSize = 0;
		fread(&szSize, strip, 1, pFile);
		for (Liar::Int k = 0; k < szSize; ++k)
		{
			Liar::Char a;
			fread(&a, szChar, 1, pFile);
			s.push_back(a);
		}
	}

	std::string MathUtils3D::ReadString(FILE* pFile)
	{
		std::string s("");
		ReadString(s, pFile);
		return s;
	}

	const Liar::DNumber MathUtils3D::MAX_VALUE = 3.40282347e+38;
	const Liar::DNumber MathUtils3D::MIN_VALUE = -3.40282347e+38;
	const Liar::DNumber MathUtils3D::ZERO_TO_LERANCE = 1e-6;
	const Liar::Number MathUtils3D::PI = 3.1415926f;
	const Liar::Number MathUtils3D::AngleToRandin = 180 / MathUtils3D::PI;
	const Liar::Number MathUtils3D::RandinToAngle = MathUtils3D::PI / 180;

	const Liar::Vector3 MathUtils3D::ZERO = Liar::Vector3(Liar::ZERO, Liar::ZERO, Liar::ZERO);
	const Liar::Vector3 MathUtils3D::ONE = Liar::Vector3(1.0f, 1.0f, 1.0f);
	const Liar::Vector3 MathUtils3D::NegativeUnitX = Liar::Vector3(-1.0f, Liar::ZERO, Liar::ZERO);
	const Liar::Vector3 MathUtils3D::UnitX = Liar::Vector3(1.0f, Liar::ZERO, Liar::ZERO);
	const Liar::Vector3 MathUtils3D::UnitY = Liar::Vector3(Liar::ZERO, 1.0f, Liar::ZERO);
	const Liar::Vector3 MathUtils3D::UnitZ = Liar::Vector3(Liar::ZERO, Liar::ZERO, 1.0f);
	const Liar::Vector3 MathUtils3D::ForwardRH = Liar::Vector3(Liar::ZERO, Liar::ZERO, -1.0f);
	const Liar::Vector3 MathUtils3D::ForwardLH = Liar::Vector3(Liar::ZERO, Liar::ZERO, 1.0f);
	const Liar::Vector3 MathUtils3D::Up = Liar::Vector3(Liar::ZERO, 1.0f, Liar::ZERO);
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