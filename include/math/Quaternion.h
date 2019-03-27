#pragma once

#include "Vector4.h"

namespace Liar
{
	class Quaternion:public Vector4
	{
	public:
		Quaternion(Liar::Number cx = Liar::ZERO, Liar::Number cy = Liar::ZERO, Liar::Number cz = Liar::ZERO, Liar::Number cw = 1.0f):Liar::Vector4(cx, cy, cz, cw) {};
		~Quaternion() {};

	public:
		/**
		*  ��ŷ����������Ԫ����˳��ΪYaw��Pitch��Roll��
		* @param	yaw yawֵ
		* @param	pitch pitchֵ
		* @param	roll rollֵ
		* @param	out �����Ԫ��
		*/
		static void CreateFromYawPitchRoll(Liar::Number yaw, Liar::Number pitch, Liar::Number roll, Liar::Quaternion& oe);
		static void CreateFromYawPitchRoll(const Liar::Vector3&, Liar::Quaternion&);

		/**
		* ����������Ԫ�����
		* @param	left left��Ԫ��
		* @param	right  right��Ԫ��
		* @param	out �����Ԫ��
		*/
		static void Multiply(const Liar::Quaternion& le, const Liar::Quaternion& re, Liar::Quaternion & oe);

		static Liar::Number ArcTanAngle(Liar::Number x, Liar::Number y);

		static void AngleTo(const Liar::Vector3& from, const Liar::Vector3& location, Liar::Vector3& angle);

		/**
		* ��ָ������ͽǶȼ�����Ԫ��
		* @param	axis  ��
		* @param	rad  �Ƕ�
		* @param	out  �����Ԫ��
		*/
		static void CreateFromAxisAngle(const Liar::Vector3& axis, Liar::Number rad, Liar::Quaternion& e);

		/**
		* �����ֵ
		* @param	left left��Ԫ��
		* @param	right  right��Ԫ��
		* @param	a ��ֵ����
		* @param	out �����Ԫ��
		* @return
		*/
		static void Slert(const Liar::Quaternion& a, const Liar::Quaternion& b, Liar::Number t, Liar::Quaternion& oe);

		/**
		* ����������Ԫ�������Բ�ֵ
		* @param	left left��Ԫ��
		* @param	right right��Ԫ��b
		* @param	t ��ֵ����
		* @param	out �����Ԫ��
		*/
		static void Lerp(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Number t, Liar::Quaternion& e);

		/**
		* ����������Ԫ���ĺ�
		* @param	left  left��Ԫ��
		* @param	right right ��Ԫ��
		* @param	out �����Ԫ��
		*/
		static void Add(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Quaternion& e);

		/**
		* ����������Ԫ���ĵ��
		* @param	left left��Ԫ��
		* @param	right right��Ԫ��
		* @return  ���
		*/
		static Liar::Number Dot(const Liar::Quaternion& f, const Liar::Quaternion& g);

		/**
		* ����۲���Ԫ��
		* @param	eye    �۲���λ��
		* @param	target Ŀ��λ��
		* @param	up     ������
		* @param	out    �����Ԫ��
		*/
		static void LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Quaternion& out);

		/**
		* ������ת�۲���Ԫ��
		* @param	forward ����
		* @param	up     ������
		* @param	out    �����Ԫ��
		*/
		static void RotationLookAt(const Liar::Vector3& forward, const Liar::Vector3& up, Liar::Quaternion& out);

		/**
		* ������Ԫ��������Ԫ����
		* @param	value ��Ԫ����
		* @param	out ����Ԫ����
		*/
		static void Invert(const Liar::Quaternion& vE, Liar::Quaternion& oE);

		// ====================== quaternion ==================
		static void CreateRotationQuaternion(const Liar::Quaternion&, Liar::Matrix4x4&);
		static void CreateFromMatrix3x3(const Liar::Matrix3x3&, Liar::Quaternion&);
		static void CreateFromMatrix4x4(const Liar::Matrix4x4&, Liar::Quaternion&);
		static void RotationMatrix(const Liar::Matrix3x3&, Liar::Quaternion&);

	public:
		/**
		* �ֽ���Ԫ����ŷ���ǣ�˳��ΪYaw��Pitch��Roll�����ο���http://xboxforums.create.msdn.com/forums/p/4574/23988.aspx#23988,������X�ᷭת������90��ʱ�У������˲�䷴ת
		* @param	quaternion Դ��Ԫ��
		* @param	out ŷ����ֵ
		*/
		void GetYawPitchRoll(Liar::Vector3& oe);

		/**
		* ����Ԫ������
		* @param	out  �����Ԫ��
		*/
		Quaternion& Invert();

		inline void Identity()
		{
			x = y = z = Liar::ZERO;
			w = 1.0f;
		}

	};

}

