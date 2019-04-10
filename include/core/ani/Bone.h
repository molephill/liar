#pragma once

#include <core/display/Node.h>
#include <core/display/Transform3D.h>

namespace Liar
{
	class Bone:public Liar::Node
	{
	public:
		Bone();
		virtual ~Bone();

	private:
		Liar::Int m_parentIndex;
		Liar::Int m_positonIndex;
		Liar::Int m_rotationIndex;
		Liar::Int m_scaleIndex;

	public:
		void SetParentIndex(Liar::Int index) {	m_parentIndex = index; };
		void SetMatrixKey(Liar::Int, Liar::Int, Liar::Int);
		Liar::Boolen Equals(const Liar::Bone&) const;
		Liar::Boolen Equals(const char*) const;
	};
}