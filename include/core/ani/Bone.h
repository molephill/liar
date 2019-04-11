#pragma once

#include <math/Matrix4x4.h>

namespace Liar
{
	class Bone
	{
	public:
		Bone();
		~Bone();

	public:
		std::string name;
		Liar::Int parentIndex;
		Liar::Int positonIndex;
		Liar::Int rotationIndex;
		Liar::Int scaleIndex;
		Liar::Matrix4x4* matrix;

	public:
		void SetMatrixKey(Liar::Int, Liar::Int, Liar::Int);
		Liar::Boolen Equals(const Liar::Bone&) const;
		Liar::Boolen Equals(const char*) const;
	};
}