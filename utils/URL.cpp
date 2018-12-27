
#include <utils/URL.h>

namespace Liar
{
	URL::URL():
		basePath(nullptr),
		baseshaderFolder(nullptr),
		baseSourceFolder(nullptr)
	{
	}


	URL::~URL()
	{
	}

	/**
	* ��ʽ��ָ���ĵ�ַ��	���ء�
	* @param	url ��ַ��
	* @param	base ·����
	* @return ��ʽ�������ĵ�ַ��
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
			/*std::string formatURL = basePath ? basePath : "";
			formatURL = baseSourceFolder ? formatURL + baseSourceFolder : formatURL;*/
			std::string formatURL = "";
			formatURL = baseSourceFolder ? formatURL + baseSourceFolder : formatURL;
			return FormatURL(url, formatURL.c_str());
		}
		else
		{
			return FormatURL(url, base);
		}
	}
}