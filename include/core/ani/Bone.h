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

	public:
		Liar::Int parentIndex;
		Liar::Int positonIndex;
		Liar::Int rotationIndex;
		Liar::Int scaleIndex;

	public:
		void SetMatrixKey(Liar::Int, Liar::Int, Liar::Int);
		Liar::Boolen Equals(const Liar::Bone&) const;
		Liar::Boolen Equals(const char*) const;
	};
}