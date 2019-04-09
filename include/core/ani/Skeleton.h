#pragma once

#include "Bone.h"

namespace Liar
{
	class Skeleton
	{
	public:
		Skeleton();
		~Skeleton();

	private:
		std::string m_name;
		Liar::Bone** m_bones;
		Liar::Uint m_numberBones;

	public:
		Liar::Boolen Equals(const Liar::Skeleton&) const;
		Liar::Boolen Equals(const char*) const;
	};
}