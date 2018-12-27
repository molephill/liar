#pragma once

#include "Geometry.h"

namespace Liar
{
	class NetGeometry:public Liar::Geometry
	{
	public:
		NetGeometry();
		~NetGeometry();

	private:
		std::string m_url;

	public:
		virtual Liar::Boolen operator==(const char*) const;
		virtual Liar::Boolen operator==(const Liar::NetGeometry&) const;

		void SetURL(const char*);

	protected:
		virtual void RecreateSubResource();
		void ReadTypeVertex(FILE*);
		void ReadTypeVertex(Liar::VertexElementAttr, Liar::Int, FILE*);
	};
}