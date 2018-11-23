#pragma once

#include <algorithm>
#include <math/Matrix4x4.h>
#include <math/Quaternion.h>

namespace Liar
{
	class Transform3D
	{
	public:
		Transform3D();
		~Transform3D();

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
		void Translate(const Liar::Vector3& translation);
		void Rotate(const Liar::Vector3& rotation, bool isRadian = true);
		void CalclateTransformation();

		void SetPosition(const Liar::Vector3& rhs);
		void SetPosition(Liar::Number x, Liar::Number y, Liar::Number z);

		void SetRotation(const Liar::Quaternion& rhs);
		void SetRotation(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w);

		void SetScale(const Liar::Vector3& rhs);
		void SetScale(Liar::Number x, Liar::Number y, Liar::Number z);

		Liar::Vector3& GetPosition() const { return *m_localPosition; };
		Liar::Quaternion& GetRotation() const { return *m_localRotation; };
		Liar::Vector3& GetScale() const { return *m_localScale; };
		Liar::Matrix4x4& GetMatrix() const { return *m_localMatrix; };
		bool GetTransformChanged() const { return m_transformChanged; };
	};
}