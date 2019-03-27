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
		*  从欧拉角生成四元数（顺序为Yaw、Pitch、Roll）
		* @param	yaw yaw值
		* @param	pitch pitch值
		* @param	roll roll值
		* @param	out 输出四元数
		*/
		static void CreateFromYawPitchRoll(Liar::Number yaw, Liar::Number pitch, Liar::Number roll, Liar::Quaternion& oe);
		static void CreateFromYawPitchRoll(const Liar::Vector3&, Liar::Quaternion&);

		/**
		* 计算两个四元数相乘
		* @param	left left四元数
		* @param	right  right四元数
		* @param	out 输出四元数
		*/
		static void Multiply(const Liar::Quaternion& le, const Liar::Quaternion& re, Liar::Quaternion & oe);

		static Liar::Number ArcTanAngle(Liar::Number x, Liar::Number y);

		static void AngleTo(const Liar::Vector3& from, const Liar::Vector3& location, Liar::Vector3& angle);

		/**
		* 从指定的轴和角度计算四元数
		* @param	axis  轴
		* @param	rad  角度
		* @param	out  输出四元数
		*/
		static void CreateFromAxisAngle(const Liar::Vector3& axis, Liar::Number rad, Liar::Quaternion& e);

		/**
		* 球面插值
		* @param	left left四元数
		* @param	right  right四元数
		* @param	a 插值比例
		* @param	out 输出四元数
		* @return
		*/
		static void Slert(const Liar::Quaternion& a, const Liar::Quaternion& b, Liar::Number t, Liar::Quaternion& oe);

		/**
		* 计算两个四元数的线性插值
		* @param	left left四元数
		* @param	right right四元数b
		* @param	t 插值比例
		* @param	out 输出四元数
		*/
		static void Lerp(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Number t, Liar::Quaternion& e);

		/**
		* 计算两个四元数的和
		* @param	left  left四元数
		* @param	right right 四元数
		* @param	out 输出四元数
		*/
		static void Add(const Liar::Quaternion& f, const Liar::Quaternion& g, Liar::Quaternion& e);

		/**
		* 计算两个四元数的点积
		* @param	left left四元数
		* @param	right right四元数
		* @return  点积
		*/
		static Liar::Number Dot(const Liar::Quaternion& f, const Liar::Quaternion& g);

		/**
		* 计算观察四元数
		* @param	eye    观察者位置
		* @param	target 目标位置
		* @param	up     上向量
		* @param	out    输出四元数
		*/
		static void LookAt(const Liar::Vector3& eye, const Liar::Vector3& target, const Liar::Vector3& up, Liar::Quaternion& out);

		/**
		* 计算旋转观察四元数
		* @param	forward 方向
		* @param	up     上向量
		* @param	out    输出四元数
		*/
		static void RotationLookAt(const Liar::Vector3& forward, const Liar::Vector3& up, Liar::Quaternion& out);

		/**
		* 计算四元数的逆四元数。
		* @param	value 四元数。
		* @param	out 逆四元数。
		*/
		static void Invert(const Liar::Quaternion& vE, Liar::Quaternion& oE);

		// ====================== quaternion ==================
		static void CreateRotationQuaternion(const Liar::Quaternion&, Liar::Matrix4x4&);
		static void CreateFromMatrix3x3(const Liar::Matrix3x3&, Liar::Quaternion&);
		static void CreateFromMatrix4x4(const Liar::Matrix4x4&, Liar::Quaternion&);
		static void RotationMatrix(const Liar::Matrix3x3&, Liar::Quaternion&);

	public:
		/**
		* 分解四元数到欧拉角（顺序为Yaw、Pitch、Roll），参考自http://xboxforums.create.msdn.com/forums/p/4574/23988.aspx#23988,问题绕X轴翻转超过±90度时有，会产生瞬间反转
		* @param	quaternion 源四元数
		* @param	out 欧拉角值
		*/
		void GetYawPitchRoll(Liar::Vector3& oe);

		/**
		* 求四元数的逆
		* @param	out  输出四元数
		*/
		Quaternion& Invert();

		inline void Identity()
		{
			x = y = z = Liar::ZERO;
			w = 1.0f;
		}

	};

}

