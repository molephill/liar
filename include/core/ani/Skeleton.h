#pragma once

#include "Bone.h"
#include <core/resource/Resource.h>
#include <core/render/TickRender.h>

namespace Liar
{
	class Skeleton:public Liar::Resource, public Liar::ITickRender
	{
	public:
		Skeleton();
		virtual ~Skeleton();

	private:
		std::string m_url;
		Liar::Bone** m_bones;
		Liar::Int m_numberBones;

		// parse
		Liar::Int m_parseVer;
		Liar::Int m_loopStep;

		// bytearray
		Liar::ByteArray* m_byteArray;

		// matrix
		Liar::Vector3** m_positions;
		Liar::Int m_numberPositons;

		Liar::Quaternion** m_rotations;
		Liar::Int m_numberRotations;

		Liar::Vector3** m_scales;
		Liar::Int m_numberScales;

	public:
		Liar::Boolen Equals(const Liar::Skeleton&) const;
		Liar::Boolen Equals(const char*) const;
		void SetURL(const char*);
		virtual bool TickRender(void* = nullptr, Liar::Int = Liar::TICK_INTERVAL);

	private:
		Liar::Boolen ParseBones(Liar::ByteArray*, Liar::Int);
		Liar::Boolen ParseMatrixInfo(Liar::ByteArray*, Liar::Int);
		void SetMatrixInfoLen(Liar::VertexElementAttr, Liar::Int);
		void SetMatrixInfo(Liar::VertexElementAttr, Liar::Int, void*);

	protected:
		virtual void DisposeResource();
		virtual void RecreateResource();
	};
}