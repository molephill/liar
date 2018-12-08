
#include <utils/URL.h>

namespace Liar
{
	URL::URL()
	{
	}


	URL::~URL()
	{
	}

	/**
	* 格式化指定的地址并	返回。
	* @param	url 地址。
	* @param	base 路径。
	* @return 格式化处理后的地址。
	*/
	std::string URL::FormatURL(const char* url, const char* base)
	{
		if (!url) return "";
		std::string formatURL;
		if (base)
		{
			formatURL = base;
		}
		else if(basePath)
		{
			formatURL = basePath;
		}
		return formatURL + url;
	}

	std::string URL::ForamtShaderURL(const char* url, const char* base)
	{
		if (!url) return "";

		if (!base)
		{
			std::string formatURL = basePath ? basePath : "";
			formatURL = baseshaderFolder ? formatURL + baseshaderFolder : formatURL;
			return FormatURL(url, formatURL.c_str());
		}
		else
		{
			return FormatURL(url, base);
		}
	}

	std::string URL::FormatSourceURL(const char* url, const char* base)
	{
		if (!url)return "";

		if (!base)
		{
			std::string formatURL = basePath ? basePath : "";
			formatURL = baseSourceFolder ? formatURL : formatURL + baseSourceFolder;
			return FormatURL(url, formatURL.c_str());
		}
		else
		{
			return FormatURL(url, base);
		}
	}
}