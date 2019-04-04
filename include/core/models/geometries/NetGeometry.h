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

	public:
		static void* ReadFloatVector(Liar::VertexFormatType, FILE*);

	protected:
		virtual void RecreateSubResource();
		void ReadDynamicVertex(Liar::GeometryVertexType, FILE*);
		void ReadTypeVertex(FILE*);
		void LoopReadTypeVertex(FILE*, Liar::Int = 2);

		// 解析各类型顶点
		void ReadIntHeapOperator(Liar::VertexElementAttr, Liar::Int, FILE*);
		void ReadSkinInfo(Liar::VertexElementAttr, Liar::Int, FILE*);
	};
}