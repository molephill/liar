#pragma once

#include <string>

#ifdef __APPLE__
#include <cctype>
#include <algorithm>
#else
#include <cctype>
#include <algorithm>
#include <windows.h>
#endif //

namespace Liar
{
	class StringParse
	{
	public:
		/**
		* 找分割符后部分
		*/
		static std::string GetLast(const std::string& name, const char* split = "\\")
		{
			std::string::size_type pos = name.find_last_of(split);
			if (pos != std::string::npos)
			{
				return name.substr(pos + 1);
			}
			else
			{
				return name;
			}
		};

		/**
		* 找分割符前部分
		*/
		static std::string GetHead(const std::string& name, const char* split = ".")
		{
			std::string::size_type pos = name.find_last_of(split);
			if (pos != std::string::npos)
			{
				return name.substr(0, pos);
			}
			else
			{
				return name;
			}
		};

		static void GetHeadAndLast(const std::string& name, std::string& head, std::string& last, const char* split = ".")
		{
			std::string::size_type pos = name.find_last_of(split);
			if (pos != std::string::npos)
			{
				head = name.substr(0, pos);
				last = name.substr(pos + 1);
			}
		}

		static void SplitHeadAndLast(const std::string& name, std::string& head, std::string& last, const char* split = ".")
		{
			std::string::size_type pos = name.find(split);
			if (pos != std::string::npos)
			{
				head = name.substr(0, pos);
				last = name.substr(pos + 1);
			}
		}

		static std::string Replace(const std::string& name, const char* rePtr, const char* ptr = "")
		{
			std::string tmp2 = name;
			std::string::size_type pos = tmp2.find(rePtr);
			while (pos != std::string::npos)
			{
				tmp2 = tmp2.replace(pos, 1, ptr);
				pos = tmp2.find(rePtr);
			}
			return tmp2;
		}

		/*
		* 获得范围内的数据
		*/
		static std::string GetRange(const std::string& name, std::string& last, const char* ptr = "\"")
		{
			std::string tmp2;
			std::string::size_type pos = name.find(ptr);
			if(pos != std::string::npos)
			{
				tmp2 = name.substr(pos + 1);
				pos = tmp2.find(ptr);
				if (pos != std::string::npos)
				{
					last = tmp2.substr(pos + 1);
					last = last.replace(pos, 1, ptr);
					return tmp2.substr(0, pos);
				}
				else
				{
					return "";
				}
			}
			else
			{
				return "";
			}
		}

		static void StringToUpper(std::string& name)
		{
			std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		}

		static void StringToLower(std::string& strExt)
		{
			std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);
		}

#ifndef __APPLE__
		static void WChar_tToString(const wchar_t* wchar, std::string& out)
		{
			DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wchar, -1, NULL, 0, NULL, FALSE);
			char *psText = new char[dwNum];
			WideCharToMultiByte(CP_OEMCP, NULL, wchar, -1, psText, dwNum, NULL, FALSE);
			out = psText;
			delete[] psText;
		};
#endif

	};
}