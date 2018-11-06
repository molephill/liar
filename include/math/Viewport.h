#pragma once

#include "Matrix4x4.h"

namespace Liar
{
	class Viewport
	{
	public:
		Viewport(float cx, float cy, float w, float h) :x(cx), y(cy), width(w), height(h), minDepth(0.0f), maxDepth(1.0f) {};
		~Viewport() {};

	public:
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;

	public:
		void Project(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4& matrixEleme, Liar::Vector3& outEleme)
		{
			Liar::Vector3::TransformV3ToV3(sourceEleme, matrixEleme, outEleme);
			float a = (((sourceEleme[0] * matrixEleme[3]) + (sourceEleme[1] * matrixEleme[7])) + (sourceEleme[2] * matrixEleme[11])) + matrixEleme[15];

			if (a != 1.0)
			{
				outEleme[0] = outEleme[0] / a;
				outEleme[1] = outEleme[1] / a;
				outEleme[2] = outEleme[2] / a;
			}

			outEleme[0] = (((outEleme[0] + 1.0) * 0.5) * width) + x;
			outEleme[1] = (((-outEleme[1] + 1.0) * 0.5) * height) + y;
			outEleme[2] = (outEleme[2] * (maxDepth - minDepth)) + minDepth;
		}

		/**
		* 反变换一个三维向量。
		* @param	source 源三维向量。
		* @param	matrix 变换矩阵。
		* @param	vector 输出三维向量。
		*/
		void UnProjectFromMat(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4 & matrixEleme, Liar::Vector3& outEleme)
		{
			outEleme[0] = (((sourceEleme[0] - x) / (width)) * 2.0) - 1.0;
			outEleme[1] = -((((sourceEleme[1] - y) / (height)) * 2.0) - 1.0);
			float halfDepth = (maxDepth - minDepth) / 2;
			outEleme[2] = (sourceEleme[2] - minDepth - halfDepth) / halfDepth;

			float a = (((outEleme[0] * matrixEleme[3]) + (outEleme[1] * matrixEleme[7])) + (outEleme[2] * matrixEleme[11])) + matrixEleme[15];
			Liar::Vector3::TransformV3ToV3(outEleme, matrixEleme, outEleme);

			if (a != 1.0)
			{
				outEleme[0] = outEleme[0] / a;
				outEleme[1] = outEleme[1] / a;
				outEleme[2] = outEleme[2] / a;
			}
		}

		/**
		* 反变换一个三维向量。
		* @param	source 源三维向量。
		* @param	projection  透视投影矩阵。
		* @param	view 视图矩阵。
		* @param	world 世界矩阵,可设置为null。
		* @param   out 输出向量。
		*/
		void UnProjectFromWVP(const Liar::Vector3& source, const Liar::Matrix4x4& projection, const Liar::Matrix4x4& view, const Liar::Matrix4x4& world, Liar::Vector3& out)
		{
			Liar::Matrix4x4::Multiply(projection, view, Liar::MathUtils3D::TEMPMatrix0);
			Liar::Matrix4x4::Multiply(Liar::MathUtils3D::TEMPMatrix0, world, Liar::MathUtils3D::TEMPMatrix0);
			Liar::MathUtils3D::TEMPMatrix0.Invert();
			UnProjectFromMat(source, Liar::MathUtils3D::TEMPMatrix0, out);
		}
	};
}

