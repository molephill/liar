
#include <core/display/Transform3D.h>

namespace Liar
{
	Transform3D::Transform3D():
		m_localPosition(new Liar::Vector3()),
		m_localRotation(new Liar::Quaternion()),
		m_localScale(new Liar::Vector3()),
		m_localMatrix(new Liar::Matrix4x4()),
		m_parent(nullptr),
		m_childs(nullptr), m_numberChild(0),
		m_pivot(nullptr), m_transformChanged(true)
	{
	}

	Transform3D::~Transform3D()
	{
		delete m_localPosition;
		delete m_localRotation;
		delete m_localScale;
		delete m_localMatrix;
		m_localPosition = nullptr;
		m_localRotation = nullptr;
		m_localScale = nullptr;
		m_localMatrix = nullptr;
		if (m_pivot)
		{
			delete m_pivot;
			m_pivot = nullptr;
		}
	}

	bool Transform3D::IsFrontFaceInvert()
	{
		bool isInvert = m_localScale->x < 0;
		if (!isInvert && m_localScale->y < 0) isInvert = !isInvert;
		if (!isInvert && m_localScale->z < 0) isInvert = !isInvert;
		return isInvert;
	}

	void Transform3D::Translate(const Liar::Vector3& translation)
	{
		Translate(translation.x, translation.y, translation.z);
	}

	void Transform3D::Translate(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (x != 0 || y != 0 || z != 0)
		{
			Liar::MathUtils3D::TEMPVector31.Set(x, y, z);
			Liar::Matrix4x4::CreateFromQuaternion(*m_localRotation, Liar::MathUtils3D::TEMPMatrix0);
			Liar::Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector31, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector30);
			Liar::Vector3::Add(*m_localPosition, Liar::MathUtils3D::TEMPVector30, *m_localPosition);
			m_transformChanged = true;
		}
	}

	void Transform3D::Rotate(const Liar::Vector3& rotation, bool isRadian)
	{
		Rotate(rotation.x, rotation.y, rotation.z, isRadian);
	}

	void Transform3D::Rotate(Liar::Number x, Liar::Number y, Liar::Number z, bool isRadian)
	{
		if (x != 0 || y != 0 || z != 0)
		{
			Liar::MathUtils3D::TEMPVector30.Set(x, y, z);
			if (!isRadian)
			{
				Liar::Vector3::Scale(Liar::MathUtils3D::TEMPVector30, Liar::MathUtils3D::AngleToRandin, Liar::MathUtils3D::TEMPVector30);
			}

			Liar::Quaternion::CreateFromYawPitchRoll(
				Liar::MathUtils3D::TEMPVector30.x,
				Liar::MathUtils3D::TEMPVector30.y,
				Liar::MathUtils3D::TEMPVector30.z,
				Liar::MathUtils3D::TEMPQuaternion0
			);

			Liar::Quaternion::Multiply(*m_localRotation, Liar::MathUtils3D::TEMPQuaternion0, *m_localRotation);
		}
	}

	void Transform3D::CalclateTransformation()
	{
		if (m_transformChanged)
		{
			m_transformChanged = false;

			if (m_pivot && !m_pivot->Equal(0.0f, 0.0f, 0.0f))
			{
				Liar::Vector3& scalePivot = Liar::MathUtils3D::TEMPVector30;
				Liar::Vector3::Multiply(*m_pivot, *m_localScale, scalePivot);
				Liar::Vector3& scaleOffsetPosition = Liar::MathUtils3D::TEMPVector31;
				Liar::Vector3::Subtract(scalePivot, *m_pivot, scaleOffsetPosition);
				Liar::Vector3& rotationOffsetPosition = Liar::MathUtils3D::TEMPVector32;
				Liar::Vector3::TransformQuat(scalePivot, *m_localRotation, rotationOffsetPosition);
				Liar::Vector3::Subtract(rotationOffsetPosition, scalePivot, rotationOffsetPosition);

				Liar::Vector3& resultLocalPosition = Liar::MathUtils3D::TEMPVector33;
				Liar::Vector3::Subtract(*m_localPosition, scaleOffsetPosition, resultLocalPosition);
				Liar::Vector3::Subtract(resultLocalPosition, rotationOffsetPosition, resultLocalPosition);

				Liar::Matrix4x4::CreateAffineTransformation(resultLocalPosition, *m_localRotation, *m_localScale, *m_localMatrix);
			}
			else
			{
				Liar::Matrix4x4::CreateAffineTransformation(*m_localPosition, *m_localRotation, *m_localScale, *m_localMatrix);
			}
		}
	}

	void Transform3D::SetPosition(const Liar::Vector3& rhs)
	{
		SetPosition(rhs.x, rhs.y, rhs.z);
	}

	void Transform3D::SetPosition(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (!m_localPosition->Equal(x, y, z))
		{
			m_localPosition->Set(x, y, z);
			m_transformChanged = true;
		}
	}

	void Transform3D::SetRotation(const Liar::Quaternion& rhs)
	{
		SetRotation(rhs.x, rhs.y, rhs.z, rhs.w);
	}

	void Transform3D::SetRotation(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		if (!m_localRotation->Equal(x, y, z, w))
		{
			m_localRotation->Set(x, y, z, w);
			m_transformChanged = true;
		}
	}

	void Transform3D::SetScale(const Liar::Vector3& rhs)
	{
		SetScale(rhs.x, rhs.y, rhs.z);
	}

	void Transform3D::SetScale(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (!m_localScale->Equal(x, y, z))
		{
			m_localScale->Set(x, y, z);
			m_transformChanged = true;
		}
	}

	void Transform3D::LookAt(const Liar::Vector3& targetE, const Liar::Vector3& up)
	{
		Liar::Vector3& eyeE = *m_localPosition;
		if (abs(eyeE[0] - targetE[0]) < MathUtils3D::ZERO_TO_LERANCE && 
			abs(eyeE[1] - targetE[1]) < MathUtils3D::ZERO_TO_LERANCE && 
			abs(eyeE[2] - targetE[2]) < MathUtils3D::ZERO_TO_LERANCE)
			return;

		Liar::Quaternion::LookAt(*m_localPosition, targetE, up, *m_localRotation);
		m_localRotation->Invert();
	}

}