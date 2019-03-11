
#include <core/display/Transform3D.h>

namespace Liar
{
	Transform3D::Transform3D():
		m_position(new Liar::Vector3()),
		m_rotation(new Liar::Quaternion()),
		m_scale(new Liar::Vector3(1.0f, 1.0f, 1.0f)),
		m_matrix(new Liar::Matrix4x4()),
		m_worldMatrix(new Liar::Matrix4x4()),
		m_projectViewMatrix(new Liar::Matrix4x4()),
		m_parent(nullptr),
		m_pivot(nullptr), m_transformChanged(true)
	{
	}

	Transform3D::~Transform3D()
	{
		delete m_position;
		delete m_rotation;
		delete m_scale;
		delete m_matrix;
		delete m_worldMatrix;
		delete m_projectViewMatrix;
		m_position = nullptr;
		m_rotation = nullptr;
		m_scale = nullptr;
		m_matrix = nullptr;
		m_worldMatrix = nullptr;
		m_projectViewMatrix = nullptr;
		m_parent = nullptr;
		if (m_pivot)
		{
			delete m_pivot;
			m_pivot = nullptr;
		}
	}

	bool Transform3D::IsFrontFaceInvert()
	{
		bool isInvert = m_scale->x < Liar::ZERO;
		if (!isInvert && m_scale->y < Liar::ZERO) isInvert = !isInvert;
		if (!isInvert && m_scale->z < Liar::ZERO) isInvert = !isInvert;
		return isInvert;
	}

	void Transform3D::Translate(const Liar::Vector3& translation)
	{
		Translate(translation.x, translation.y, translation.z);
	}

	void Transform3D::Translate(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (x != Liar::ZERO || y != Liar::ZERO || z != Liar::ZERO)
		{
			Liar::MathUtils3D::TEMPVector31.Set(x, y, z);
			Liar::Matrix4x4::CreateFromQuaternion(*m_rotation, Liar::MathUtils3D::TEMPMatrix0);
			Liar::Vector3::TransformCoordinate(Liar::MathUtils3D::TEMPVector31, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector30);
			Liar::Vector3::Add(*m_position, Liar::MathUtils3D::TEMPVector30, *m_position);
			m_transformChanged = true;
		}
	}

	void Transform3D::Rotate(const Liar::Vector3& rotation, bool isRadian)
	{
		Rotate(rotation.x, rotation.y, rotation.z, isRadian);
	}

	void Transform3D::Rotate(Liar::Number x, Liar::Number y, Liar::Number z, bool isRadian)
	{
		if (x != Liar::ZERO || y != Liar::ZERO || z != Liar::ZERO)
		{
			Liar::MathUtils3D::TEMPVector30.Set(x, y, z);
			if (!isRadian)
			{
				Liar::Vector3::Scale(Liar::MathUtils3D::TEMPVector30, Liar::MathUtils3D::AngleToRandin, Liar::MathUtils3D::TEMPVector30);
			}

			Liar::Quaternion::CreateFromYawPitchRoll(
				Liar::MathUtils3D::TEMPVector30,
				Liar::MathUtils3D::TEMPQuaternion0
			);

			Liar::Quaternion::Multiply(*m_rotation, Liar::MathUtils3D::TEMPQuaternion0, *m_rotation);
			m_transformChanged = true;
		}
	}

	void Transform3D::CalclateTransformation(Liar::Matrix4x4* projectionViewMatrix)
	{
		if (m_transformChanged)
		{
			m_transformChanged = false;

			if (m_pivot && !m_pivot->Equal(Liar::ZERO, Liar::ZERO, Liar::ZERO))
			{
				Liar::Vector3& scalePivot = Liar::MathUtils3D::TEMPVector30;
				Liar::Vector3::Multiply(*m_pivot, *m_scale, scalePivot);
				Liar::Vector3& scaleOffsetPosition = Liar::MathUtils3D::TEMPVector31;
				Liar::Vector3::Subtract(scalePivot, *m_pivot, scaleOffsetPosition);
				Liar::Vector3& rotationOffsetPosition = Liar::MathUtils3D::TEMPVector32;
				Liar::Vector3::TransformQuat(scalePivot, *m_rotation, rotationOffsetPosition);
				Liar::Vector3::Subtract(rotationOffsetPosition, scalePivot, rotationOffsetPosition);

				Liar::Vector3& resultLocalPosition = Liar::MathUtils3D::TEMPVector33;
				Liar::Vector3::Subtract(*m_position, scaleOffsetPosition, resultLocalPosition);
				Liar::Vector3::Subtract(resultLocalPosition, rotationOffsetPosition, resultLocalPosition);

				Liar::Matrix4x4::CreateAffineTransformation(resultLocalPosition, *m_rotation, *m_scale, *m_matrix);
			}
			else
			{
				Liar::Matrix4x4::CreateAffineTransformation(*m_position, *m_rotation, *m_scale, *m_matrix);
			}

			if (m_parent)
			{
				Liar::Matrix4x4::Multiply(*(m_parent->m_worldMatrix), *m_matrix, *m_worldMatrix);
			}
			else
			{
				m_worldMatrix->Set(*m_matrix);
			}
		}

		if (projectionViewMatrix)
		{
			Liar::Matrix4x4::Multiply(*projectionViewMatrix, *m_worldMatrix, *m_projectViewMatrix);
		}
	}

	void Transform3D::SetPosition(const Liar::Vector3& rhs)
	{
		SetPosition(rhs.x, rhs.y, rhs.z);
	}

	void Transform3D::SetPosition(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (!m_position->Equal(x, y, z))
		{
			m_position->Set(x, y, z);
			m_transformChanged = true;
		}
	}

	void Transform3D::SetRotation(const Liar::Quaternion& rhs)
	{
		SetRotation(rhs.x, rhs.y, rhs.z, rhs.w);
	}

	void Transform3D::SetRotation(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
	{
		if (!m_rotation->Equal(x, y, z, w))
		{
			m_rotation->Set(x, y, z, w);
			m_transformChanged = true;
		}
	}

	void Transform3D::SetRotation(const Liar::Vector3& rhs)
	{
		SetRotation(rhs.x, rhs.y, rhs.z);
	}

	void Transform3D::SetRotation(Liar::Number yaw, Liar::Number pitch, Liar::Number roll)
	{
		Liar::Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll, Liar::MathUtils3D::TEMPQuaternion0);
		SetRotation(Liar::MathUtils3D::TEMPQuaternion0);
	}

	void Transform3D::SetScale(const Liar::Vector3& rhs)
	{
		SetScale(rhs.x, rhs.y, rhs.z);
	}

	void Transform3D::SetScale(Liar::Number x, Liar::Number y, Liar::Number z)
	{
		if (!m_scale->Equal(x, y, z))
		{
			m_scale->Set(x, y, z);
			m_transformChanged = true;
		}
	}

	void Transform3D::SetParent(Liar::Transform3D* parent)
	{
		if (parent != m_parent)
		{
			m_parent = parent;
			m_transformChanged = true;
		}
	}

	void Transform3D::LookAt(const Liar::Vector3& targetE, const Liar::Vector3& up)
	{
		Liar::Vector3& eyeE = *m_position;
		if (abs(eyeE[0] - targetE[0]) < MathUtils3D::ZERO_TO_LERANCE && 
			abs(eyeE[1] - targetE[1]) < MathUtils3D::ZERO_TO_LERANCE && 
			abs(eyeE[2] - targetE[2]) < MathUtils3D::ZERO_TO_LERANCE)
			return;

		Liar::Quaternion::LookAt(*m_position, targetE, up, *m_rotation);
		m_rotation->Invert();
	}

}