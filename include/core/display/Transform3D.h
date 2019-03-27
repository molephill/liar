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
		Liar::Vector3* m_position;
		Liar::Quaternion* m_rotation;
		Liar::Vector3* m_scale;
		Liar::Matrix4x4* m_matrix;
		Liar::Matrix4x4* m_worldMatrix;
		Liar::Matrix4x4* m_projectViewMatrix;

		Liar::Transform3D* m_parent;
		Liar::Vector3* m_pivot;

		bool m_transformChanged;

	public:
		void Translate(const Liar::Vector3& translation);
		void Translate(Liar::Number, Liar::Number, Liar::Number);
		void Rotate(const Liar::Vector3& rotation, bool isRadian = true);
		void Rotate(Liar::Number, Liar::Number, Liar::Number, bool isRadian = true);
		void CalclateTransformation(Liar::Matrix4x4* mat = nullptr);

		void SetPosition(const Liar::Vector3& rhs);
		void SetPosition(Liar::Number x, Liar::Number y, Liar::Number z);

		void SetRotation(const Liar::Quaternion& rhs);
		void SetRotation(Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number w);
		void SetRotation(const Liar::Vector3&);
		void SetRotation(Liar::Number, Liar::Number, Liar::Number);

		void SetScale(const Liar::Vector3& rhs);
		void SetScale(Liar::Number);
		void SetScale(Liar::Number x, Liar::Number y, Liar::Number z);

		void SetParent(Liar::Transform3D* parent);

		bool IsFrontFaceInvert();

		Liar::Matrix4x4& GetProjectionViewWorldMatrix() const { return *m_projectViewMatrix; };
		Liar::Vector3& GetPosition() const { return *m_position; };
		Liar::Quaternion& GetRotation() const { return *m_rotation; };
		Liar::Vector3& GetScale() const { return *m_scale; };
		Liar::Matrix4x4& GetMatrix() const { return *m_matrix; };
		Liar::Matrix4x4& GetWorldMatrix() const { return *m_worldMatrix; };
		bool GetTransformChanged() const { return m_transformChanged; };
		/**
		* 观察目标位置。
		* @param	target 观察目标。
		* @param	up 向上向量。
		*/
		void LookAt(const Liar::Vector3&, const Liar::Vector3&);
	};
}