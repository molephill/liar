#include <core/ani/Bone.h>

namespace Liar
{
	Bone::Bone():
		Liar::Node(),
		parentIndex(-1),
		positonIndex(0), rotationIndex(0), scaleIndex(0)
	{
	}


	Bone::~Bone()
	{
	}

	void Bone::SetMatrixKey(Liar::Int pos, Liar::Int rot, Liar::Int scale)
	{
		positonIndex = pos;
		rotationIndex = rot;
		scaleIndex = scale;
	}

	Liar::Boolen Bone::Equals(const Liar::Bone& bone) const
	{
		return Equals(bone.m_name.c_str());
	}

	Liar::Boolen Bone::Equals(const char* name) const
	{
		return m_name == name;
	}
}
