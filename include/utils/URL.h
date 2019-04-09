#pragma once

#include <string>

namespace Liar
{
	class URL
	{
	public:
		URL();
		~URL();

	public:
		const char* basePath;
		const char* baseShaderFolder;
		const char* baseSourceFolder;
		const char* baseSkeletonFolder;

		std::string FormatURL(const char*, const char* = nullptr);
		std::string ForamtShaderURL(const char*, const char* = nullptr);
		std::string FormatSourceURL(const char*, const char* = nullptr);
		std::string FormatSkeletonURL(const char*, const char* = nullptr);
	};
}
