#pragma once

#include "Geometry.h"

namespace Liar
{
	class NetGeometry:public Liar::Geometry, public Liar::ITickRender
	{
	public:
		NetGeometry();
		virtual ~NetGeometry();

	private:
		std::string m_url;
		Liar::Int m_loopStep;

	public:
		virtual Liar::Boolen operator==(const char*) const;
		virtual Liar::Boolen operator==(const Liar::NetGeometry&) const;

		void SetURL(const char*);

		// ∑÷÷°¥¶¿Ì
		virtual bool TickRender(void* = nullptr, Liar::Int = Liar::TICK_INTERVAL);

	protected:
		virtual bool RecreateSubResource();
		// read bytearray
		void ParseSubRawData();
		void ParseIntHeapOperator(Liar::VertexElementAttr, Liar::Int);
		void ParseSkinData(Liar::VertexElementAttr, Liar::Int);
	};
}