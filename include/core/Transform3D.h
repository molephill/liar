#pragma once

#include <math/Matrix4x4.h>
#include <math/Quaternion.h>

namespace Liar
{
	class Transform3D
	{
	public:
		Transform3D():
			m_localPosition(new Liar::Vector3()), m_localRotation(new Liar::Quaternion()), m_localScale(new Liar::Vector3(1.0f, 1.0f, 1.0f)), m_localMatrix(new Liar::Matrix4x4()),
			m_parent(nullptr), m_childs(nullptr), m_numberChild(0), m_pivot(nullptr),
			m_transformChanged(true)
		{};
		~Transform3D()
		{
			delete m_localPosition;
			delete m_localRotation;
			delete m_localScale;
			delete m_localMatrix;
		};

	private:
		Liar::Vector3* m_localPosition;
		Liar::Quaternion* m_localRotation;
		Liar::Vector3* m_localScale;
		Liar::Matrix4x4* m_localMatrix;

		Liar::Transform3D* m_parent;
		Liar::Transform3D** m_childs;
		Liar::Uint m_numberChild;

		Liar::Vector3* m_pivot;

		bool m_transformChanged;

	public:
		void Translate(const Liar::Vector3& translation)
		{
			if (translation != 0)
			{
				Liar::MathUtils3D::CreateFromQuaternion(*m_localRotation, Liar::MathUtils3D::TEMPMatrix0);
				Liar::MathUtils3D::TransformCoordinate(translation, Liar::MathUtils3D::TEMPMatrix0, Liar::MathUtils3D::TEMPVector30);
				Liar::Vector3::Add(*m_localPosition, Liar::MathUtils3D::TEMPVector30, *m_localPosition);
				m_transformChanged = true;
			}
		};

		void Rotate(const Liar::Vector3& rotation, bool isRadian = true)
		{
			if (rotation != 0)
			{
				Liar::MathUtils3D::TEMPVector30.Set(rotation);
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

		void CalclateTransformation()
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
					Liar::MathUtils3D::TransformQuat(scalePivot, *m_localRotation, rotationOffsetPosition);
					Liar::Vector3::Subtract(rotationOffsetPosition, scalePivot, rotationOffsetPosition);

					Liar::Vector3& resultLocalPosition = Liar::MathUtils3D::TEMPVector33;
					Liar::Vector3::Subtract(*m_localPosition, scaleOffsetPosition, resultLocalPosition);
					Liar::Vector3::Subtract(resultLocalPosition, rotationOffsetPosition, resultLocalPosition);

					Liar::MathUtils3D::CreateAffineTransformation(resultLocalPosition, *m_localRotation, *m_localScale, *m_localMatrix);
				}
				else
				{
					Liar::MathUtils3D::CreateAffineTransformation(*m_localPosition, *m_localRotation, *m_localScale, *m_localMatrix);
				}
			}
		}

		inline void SetPosition(const Liar::Vector3& rhs)
		{
			if (!m_localPosition->Equal(rhs))
			{
				m_localPosition->Set(rhs);
				m_transformChanged = true;
			}
		};

		inline void SetPosition(Liar::Number x, Liar::Number y, Liar::Number z)
		{
			if (!m_localPosition->Equal(x, y, z))
			{
				m_localPosition->Set(x, y, z);
				m_transformChanged = true;
			}
		};

		inline void SetRotation(const Liar::Quaternion& rhs)
		{
			if (!m_localRotation->Equal(rhs))
			{
				m_localRotation->Set(rhs);
				m_transformChanged = true;
			}
		}

		inline void SetRotation(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w)
		{
			if (!m_localRotation->Equal(x, y, z, w))
			{
				m_localRotation->Set(x, y, z, w);
				m_transformChanged = true;
			}
		}

		inline void SetScale(const Liar::Vector3& rhs)
		{
			if (!m_localScale->Equal(rhs))
			{
				m_localScale->Set(rhs);
				m_transformChanged = true;
			}
		}

		inline void SetScale(Liar::Number x, Liar::Number y, Liar::Number z)
		{
			if (!m_localScale->Equal(x, y, z))
			{
				m_localScale->Set(x, y, z);
				m_transformChanged = true;
			}
		}

		Liar::Vector3& GetPosition() const { return *m_localPosition; };
		Liar::Quaternion& GetRotation() const { return *m_localRotation; };
		Liar::Vector3& GetScale() const { return *m_localScale; };
		Liar::Matrix4x4& GetMatrix() const { return *m_localMatrix; };
		bool GetTransformChanged() const { return m_transformChanged; };
	};
}