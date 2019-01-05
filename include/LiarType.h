#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <math.h>

namespace Liar
{
	typedef unsigned int Uint;
	typedef int Int;
	typedef float Number;
	typedef double DNumber;
	typedef unsigned char UChar;
	typedef char Char;
	typedef bool Boolen;

	// funcction
	class Event;
	typedef void(*EventFun)(const Liar::Event&);

	// 定义类类型
	enum ClassType
	{
		CLASS_NODE_TYPE_NODE,
		CLASS_NODE_TYPE_MESH,
		CLASS_NODE_TYPE_MODEL,
		CLASS_NODE_TYPE_STAGE
	};
}