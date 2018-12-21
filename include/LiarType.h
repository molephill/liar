#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

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
}