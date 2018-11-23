#pragma once
#include <core/models/BaseMesh.h>

namespace Liar
{
	class BoxMesh :public BaseMesh
	{
	public:
		BoxMesh(Liar::Number l = 1.0f, Liar::Number w = 1.0f, Liar::Number h = 1.0f);
		virtual ~BoxMesh();

	private:
		Liar::Number m_long;
		Liar::Number m_width;
		Liar::Number m_height;

	public:
		Liar::Number GetLong() const { return m_long; };
		Liar::Number GetWidth() const { return m_width; };
		Liar::Number GetHeight() const { return m_height; };
		void SetLong(Liar::Number value);
		void SetWidth(Liar::Number value);
		void SetHeight(Liar::Number value);

	protected:
		virtual void RecreateResource();

	public:
		virtual size_t GetNumberTriangles() const { return 12; };
		virtual void Render(Liar::RenderState&);
	};
}