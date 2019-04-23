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
		Liar::Int m_loopStep;
		Liar::ByteArray* m_byteArray;

	public:
		virtual void SetURL(const char*);

		// ∑÷÷°¥¶¿Ì
		virtual bool TickRender(void* = nullptr, Liar::Int = Liar::TICK_INTERVAL);
		virtual void DisposeResource();

	protected:
		virtual bool RecreateSubResource();
		// read bytearray
		void ParseSubRawData();
		void ParseIntHeapOperator(Liar::VertexElementAttr, Liar::Int);
		void ParseSkinData(Liar::VertexElementAttr, Liar::Int);
	};
}