
#include <math/Viewport.h>

namespace Liar
{
	Viewport::Viewport(Liar::Number cx, Liar::Number cy, Liar::Number w, Liar::Number h)
	{
		Init(cx, cy, w, h);
	}

	Viewport::~Viewport()
	{

	}

	void Viewport::Init(Liar::Number cx, Liar::Number cy, Liar::Number w, Liar::Number h)
	{
		m_x = cx;
		m_y = cy;
		m_width = w;
		m_height = h;
		m_minDepth = 0.0f;
		m_maxDepth = 1.0f;
	}

	/**
	* 变换一个三维向量。
	* @param	source 源三维向量。
	* @param	matrix 变换矩阵。
	* @param	vector 输出三维向量。
	*/
	void Viewport::Project(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4& matrixEleme, Liar::Vector3& outEleme)
	{
		Liar::Vector3::TransformV3ToV3(sourceEleme, matrixEleme, outEleme);
		Liar::Number a = (((sourceEleme[0] * matrixEleme[3]) + (sourceEleme[1] * matrixEleme[7])) + (sourceEleme[2] * matrixEleme[11])) + matrixEleme[15];

		if (a != 1.0)
		{
			outEleme[0] = outEleme[0] / a;
			outEleme[1] = outEleme[1] / a;
			outEleme[2] = outEleme[2] / a;
		}

		outEleme[0] = (((outEleme[0] + 1.0f) * 0.5f) * m_width) + m_x;
		outEleme[1] = (((-outEleme[1] + 1.0f) * 0.5f) * m_height) + m_y;
		outEleme[2] = (outEleme[2] * (m_maxDepth - m_minDepth)) + m_minDepth;
	}

	/**
	* 反变换一个三维向量。
	* @param	source 源三维向量。
	* @param	matrix 变换矩阵。
	* @param	vector 输出三维向量。
	*/
	void Viewport::UnProjectFromMat(const Liar::Vector3& sourceEleme, const Liar::Matrix4x4 & matrixEleme, Liar::Vector3& outEleme)
	{
		outEleme[0] = (((sourceEleme[0] - m_x) / (m_width)) * 2.0f) - 1.0f;
		outEleme[1] = -((((sourceEleme[1] - m_y) / (m_height)) * 2.0f) - 1.0f);
		Liar::Number halfDepth = (m_maxDepth - m_minDepth) / 2.0f;
		outEleme[2] = (sourceEleme[2] - m_minDepth - halfDepth) / halfDepth;

		Liar::Number a = (((outEleme[0] * matrixEleme[3]) + (outEleme[1] * matrixEleme[7])) + (outEleme[2] * matrixEleme[11])) + matrixEleme[15];
		Liar::Vector3::TransformV3ToV3(outEleme, matrixEleme, outEleme);

		if (a != 1.0f)
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
	void Viewport::UnProjectFromWVP(const Liar::Vector3& source, const Liar::Matrix4x4& projection, const Liar::Matrix4x4& view, const Liar::Matrix4x4* world, Liar::Vector3& out)
	{
		Liar::Matrix4x4::Multiply(projection, view, Liar::MathUtils3D::TEMPMatrix0);
		if (world) Liar::Matrix4x4::Multiply(Liar::MathUtils3D::TEMPMatrix0, *world, Liar::MathUtils3D::TEMPMatrix0);
		Liar::MathUtils3D::TEMPMatrix0.Invert();
		UnProjectFromMat(source, Liar::MathUtils3D::TEMPMatrix0, out);
	}

	void Viewport::SetStartXY(Liar::Number x, Liar::Number y)
	{
		m_x = x;
		m_y = y;
	}

	void Viewport::SetViewSize(Liar::Number w, Liar::Number h)
	{
		m_width = w;
		m_height = h;
	}
}