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
		const char* baseshaderFolder;
		const char* baseSourceFolder;

		std::string FormatURL(const char*, const char* base = nullptr);
		std::string ForamtShaderURL(const char*, const char* base = nullptr);
		std::string FormatSourceURL(const char*, const char* base = nullptr);
	};
}
