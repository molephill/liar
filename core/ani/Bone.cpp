#include <core/ani/Bone.h>

namespace Liar
{
	Bone::Bone():
		Liar::Node(),
		m_parentIndex(-1),
		m_positonIndex(0), m_rotationIndex(0), m_scaleIndex(0)
	{
	}


	Bone::~Bone()
	{
	}

	void Bone::SetMatrixKey(Liar::Int pos, Liar::Int rot, Liar::Int scale)
	{
		m_positonIndex = pos;
		m_rotationIndex = rot;
		m_scaleIndex = scale;
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
