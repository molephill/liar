#pragma once

#include "Geometry.h"
#include <math/ByteArray.h>

namespace Liar
{
	class NetGeometry:public Liar::Geometry
	{
	public:
		NetGeometry();
		virtual ~NetGeometry();

	private:
		std::string m_url;
		Liar::ByteArray* m_byteArray;
		Liar::Int m_readStep;
		Liar::Int m_loopStep;

	public:
		virtual Liar::Boolen operator==(const char*) const;
		virtual Liar::Boolen operator==(const Liar::NetGeometry&) const;

		void SetURL(const char*);

	protected:
		virtual void RecreateSubResource();
		// read bytearray
		void ParseRawData();
		void ParseSubRawData();
		void Loop(Liar::Int = 4);
		void ParseIntHeapOperator(Liar::VertexElementAttr, Liar::Int);
		void ParseSkinData(Liar::VertexElementAttr, Liar::Int);
	};
}