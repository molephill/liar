#pragma once

#include "Geometry.h"

namespace Liar
{
	class BoxGeometry:public Geometry
	{
	public:
		BoxGeometry(Liar::Number l = 1.0f, Liar::Number w = 1.0f, Liar::Number h = 1.0f);
		virtual ~BoxGeometry();

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
		//virtual void RecreateResource();
		virtual void RecreateSubResource();

		/*
		* ÉèÖÃ¶¥µãË÷Òý
		* 
		*/
		void SetVertexKey(Liar::Int, Liar::Uint, Liar::Uint normalIndex = 0, Liar::Uint texIndex = 0);
	};
}