#include <core/ani/Bone.h>

namespace Liar
{
	Bone::Bone():
		name(""),
		parentIndex(-1),
		positonIndex(0), rotationIndex(0), scaleIndex(0),
		matrix(new Liar::Matrix4x4())
	{
	}


	Bone::~Bone()
	{
		delete matrix;
		matrix = nullptr;
	}

	void Bone::SetMatrixKey(Liar::Int pos, Liar::Int rot, Liar::Int scale)
	{
		positonIndex = pos;
		rotationIndex = rot;
		scaleIndex = scale;
	}

	Liar::Boolen Bone::Equals(const Liar::Bone& bone) const
	{
		return Equals(bone.name.c_str());
	}

	Liar::Boolen Bone::Equals(const char* name) const
	{
		return this->name == name;
	}
}
