#pragma once

#include "Matrix4x4.h"

namespace Liar
{
	class Viewport
	{
	public:
		Viewport(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number w = 0.0f, Liar::Number h = 0.0f);
		~Viewport();

	private:
		Liar::Number m_x;
		Liar::Number m_y;
		Liar::Number m_width;
		Liar::Number m_height;
		Liar::Number m_minDepth;
		Liar::Number m_maxDepth;

	public:
		void Init(Liar::Number cx = 0.0f, Liar::Number cy = 0.0f, Liar::Number w = 0.0f, Liar::Number h = 0.0f);
		void Project(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4& matrixEleme, Liar::Vector3& outEleme);

		/**
		* 反变换一个三维向量。
		* @param	source 源三维向量。
		* @param	matrix 变换矩阵。
		* @param	vector 输出三维向量。
		*/
		void UnProjectFromMat(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4 & matrixEleme, Liar::Vector3& outEleme);

		/**
		* 反变换一个三维向量。
		* @param	source 源三维向量。
		* @param	projection  透视投影矩阵。
		* @param	view 视图矩阵。
		* @param	world 世界矩阵,可设置为null。
		* @param   out 输出向量。
		*/
		void UnProjectFromWVP(const Liar::Vector3& source, const Liar::Matrix4x4& projection, const Liar::Matrix4x4& view, const Liar::Matrix4x4* world, Liar::Vector3& out);

		void SetStartXY(Liar::Number, Liar::Number);
		void SetViewSize(Liar::Number, Liar::Number);

		Liar::Number GetAspect() const { return m_width / m_height; };
	};
}

